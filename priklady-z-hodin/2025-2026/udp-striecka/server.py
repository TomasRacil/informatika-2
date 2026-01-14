import socket
import json
import time
import math
import pygame
import sys
import random

# Konfigurace sítě
HOST = '127.0.0.1'
PORT = 65432

# Konfigurace hry
WIDTH, HEIGHT = 800, 600
PLAYER_RADIUS = 15
BULLET_RADIUS = 5
BG_COLOR = (20, 20, 20)
PLAYER_COLOR = (0, 255, 0)
BULLET_COLOR = (255, 255, 0)
TEXT_COLOR = (255, 255, 255)
FPS = 60

# Herní konstanty
PLAYER_SPEED = 3
ROTATION_SPEED = 2 # stupně za tick
PLAYER_TIMEOUT = 5.0
BULLET_SPEED = 10
BULLET_LIFETIME = 50
SHOOT_COOLDOWN = 0.2 # sekundy
RESPAWN_TIME = 3.0 # sekundy

# Inicializace Pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("UDP Server - Authority & Monitoring")
clock = pygame.time.Clock()
font = pygame.font.SysFont("Arial", 18)

# Inicializace Socketu
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((HOST, PORT))
server_socket.setblocking(False)

print(f"Server běží na {HOST}:{PORT}")

# Permanentní statistiky: { "nickname": { "kills": 0, "deaths": 0 } }
global_scores = {}

# Aktivní hráči: { "ip:port": { ... stav ... } }
players = {}
bullets = [] 

def get_random_spawn():
    return random.randint(50, WIDTH-50), random.randint(50, HEIGHT-50)

def draw_player(surface, x, y, angle, color, label=None):
    rad = math.radians(angle)
    # Body trojúhelníku
    tip_x = x + math.cos(rad) * 20
    tip_y = y + math.sin(rad) * 20
    left_x = x + math.cos(rad + 2.5) * 20
    left_y = y + math.sin(rad + 2.5) * 20
    right_x = x + math.cos(rad - 2.5) * 20
    right_y = y + math.sin(rad - 2.5) * 20
    
    pygame.draw.polygon(surface, color, [(tip_x, tip_y), (left_x, left_y), (right_x, right_y)])
    if label:
        text = font.render(label, True, TEXT_COLOR)
        surface.blit(text, (x - text.get_width() // 2, y - 35))

def check_collisions():
    global bullets, players, global_scores
    active_bullets = []
    current_time = time.time()
    
    for b in bullets:
        b["x"] += b["dx"]
        b["y"] += b["dy"]
        b["life"] -= 1
        
        hit = False
        if b["life"] > 0:
            for pid, p in players.items():
                if p.get("dead_until", 0) > current_time:
                    continue # Mrtvé hráče nelze zasáhnout

                if pid != b["owner_id"]: 
                    dist = math.sqrt((b["x"] - p["x"])**2 + (b["y"] - p["y"])**2)
                    if dist < (PLAYER_RADIUS + BULLET_RADIUS):
                        print(f"Hráč {p['nickname']} byl zasažen!")
                        
                        # Kill pro střelce (pokud je online)
                        shooter_nick = b["owner_nick"]
                        if shooter_nick in global_scores:
                             global_scores[shooter_nick]["kills"] += 1

                        # Smrt pro oběť
                        victim_nick = p["nickname"]
                        if victim_nick in global_scores:
                             global_scores[victim_nick]["deaths"] += 1
                        
                        # Set death timer (místo okamžitého respawnu)
                        p["dead_until"] = current_time + RESPAWN_TIME
                        
                        hit = True
                        break 
            
            if not hit:
                active_bullets.append(b)
    
    bullets = active_bullets

def update_physics():
    global players
    current_time = time.time()
    
    for pid, p in players.items():
        # Kontrola, zda je hráč mrtvý
        if p.get("dead_until", 0) > current_time:
            continue # Mrtvý hráč se nehýbe a nestřílí

        # Pokud se právě respawnul (dead_until expiroval, ale ještě jsme ho neposunuli)
        # To se stane implicitně, pokud byl předtím mrtvý. 
        # Ale my chceme, aby po smrti zmizel.
        # Takže pokud `dead_until` vypršel, musíme zkontrolovat, jestli už byl respawnut.
        # Uděláme to tak, že `dead_until` nastavíme na 0, když respawneme.
        pass # Logika je řešena v main loop pro respawn

        keys = p.get("keys", {})
        
        # Rotace
        if keys.get("left"):
            p["angle"] -= ROTATION_SPEED
        if keys.get("right"):
            p["angle"] += ROTATION_SPEED
            
        # Pohyb
        rad = math.radians(p["angle"])
        dx = 0
        dy = 0
        if keys.get("up"):
            dx += math.cos(rad) * PLAYER_SPEED
            dy += math.sin(rad) * PLAYER_SPEED
        if keys.get("down"):
            dx -= math.cos(rad) * PLAYER_SPEED
            dy -= math.sin(rad) * PLAYER_SPEED
            
        p["x"] += dx
        p["y"] += dy
        
        # Omezení na mapu
        p["x"] = max(0, min(WIDTH, p["x"]))
        p["y"] = max(0, min(HEIGHT, p["y"]))
        
        # Střelba (s cooldownem)
        if keys.get("shoot"):
            now = time.time()
            if now - p["last_shot"] > SHOOT_COOLDOWN:
                p["last_shot"] = now
                # Vytvoření kulky
                angle_rad = math.radians(p["angle"])
                bx = p["x"] + math.cos(angle_rad) * 20
                by = p["y"] + math.sin(angle_rad) * 20
                bullets.append({
                    "x": bx,
                    "y": by,
                    "dx": math.cos(angle_rad) * BULLET_SPEED,
                    "dy": math.sin(angle_rad) * BULLET_SPEED,
                    "owner_id": pid,
                    "owner_nick": p["nickname"],
                    "life": BULLET_LIFETIME
                })

def main():
    running = True
    while running:
        clock.tick(FPS)
        current_time = time.time()
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # --- NETWORK RECEIVE ---
        try:
            while True:
                data, addr = server_socket.recvfrom(1024)
                addr_key = f"{addr[0]}:{addr[1]}"
                
                try:
                    msg = json.loads(data.decode('utf-8'))
                    
                    # Explicitní odpojení
                    if msg.get("cmd") == "disconnect":
                        if addr_key in players:
                            print(f"Odpojen (explicitně): {players[addr_key]['nickname']}")
                            del players[addr_key]
                        continue

                    nick = msg.get("nickname", "Unknown")
                    
                    if nick not in global_scores:
                        global_scores[nick] = {"kills": 0, "deaths": 0}
                    
                    if addr_key not in players:
                        print(f"Připojen: {nick} ({addr_key})")
                        sx, sy = get_random_spawn()
                        players[addr_key] = {
                            "x": sx, "y": sy, "angle": 0,
                            "nickname": nick,
                            "last_seen": time.time(),
                            "last_shot": 0,
                            "keys": {},
                            "dead_until": 0
                        }
                    
                    p = players[addr_key]
                    p["last_seen"] = time.time()
                    p["nickname"] = nick 
                    p["keys"] = msg.get("keys", {})
                    
                except json.JSONDecodeError:
                    pass
        except BlockingIOError:
            pass
        except ConnectionResetError:
            pass 

        # --- LOGIC ---
        to_remove = []
        for pid, p in players.items():
            # Respawn check
            if p.get("dead_until", 0) != 0 and current_time > p["dead_until"]:
                 p["dead_until"] = 0
                 p["x"], p["y"] = get_random_spawn()
                 print(f"Hráč {p['nickname']} respawnut.")

            if current_time - p["last_seen"] > PLAYER_TIMEOUT:
                to_remove.append(pid)
                
        for pid in to_remove:
            print(f"Odpojen (timeout): {players[pid]['nickname']}")
            del players[pid]

        update_physics()
        check_collisions()
        
        # Leaderboard
        sorted_lb = []
        for nick, stats in global_scores.items():
            ratio = stats["kills"] / max(1, stats["deaths"])
            sorted_lb.append({
                "nickname": nick,
                "kills": stats["kills"],
                "deaths": stats["deaths"],
                "ratio": ratio
            })
        sorted_lb.sort(key=lambda x: x["ratio"], reverse=True)

        # --- NETWORK BROADCAST ---
        # Posíláme VŠECHNY hráče + info o smrti
        display_players = []
        for p in players.values():
            is_dead = p.get("dead_until", 0) > current_time
            display_players.append({
                "x": p["x"], 
                "y": p["y"], 
                "angle": p["angle"], 
                "nickname": p["nickname"],
                "is_dead": is_dead,
                "respawn_in": max(0, p.get("dead_until", 0) - current_time)
            })
                
        game_state = {
            "players": display_players,
            "bullets": [{"x": b["x"], "y": b["y"]} for b in bullets],
            "leaderboard": sorted_lb
        }
        state_json = json.dumps(game_state).encode('utf-8')
        
        for pid in players.keys():
            try:
                ip, port = pid.split(":")
                server_socket.sendto(state_json, (ip, int(port)))
            except Exception:
                pass
                
        # --- DRAWING (MONITORING) ---
        screen.fill(BG_COLOR)
        
        info_text = f"Active: {len(players)} | Bullets: {len(bullets)} | FPS: {int(clock.get_fps())}"
        screen.blit(font.render(info_text, True, TEXT_COLOR), (10, 10))
        
        for p in players.values():
            if p.get("dead_until", 0) > current_time:
                continue # Nevykreslovat mrtvé na serveru
            
            stats = global_scores.get(p["nickname"], {"kills":0, "deaths":0})
            label = f"{p['nickname']} ({stats['kills']}/{stats['deaths']})"
            draw_player(screen, p["x"], p["y"], p["angle"], PLAYER_COLOR, label)
            
        for b in bullets:
            pygame.draw.circle(screen, BULLET_COLOR, (int(b["x"]), int(b["y"])), 3)
            
        # Draw Leaderboard
        y_off = 40
        for entry in sorted_lb:
            is_online = any(p["nickname"] == entry["nickname"] for p in players.values())
            color = (255, 255, 255) if is_online else (100, 100, 100)
            
            l_text = f"{entry['nickname']}: {entry['kills']}K / {entry['deaths']}D (R: {entry['ratio']:.2f})"
            screen.blit(font.render(l_text, True, color), (10, y_off))
            y_off += 20
            
        pygame.display.flip()

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()
