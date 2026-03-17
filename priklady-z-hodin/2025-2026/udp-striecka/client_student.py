import pygame
import socket
import json
import math
import sys

# Konfigurace
HOST = input("Zadej IP serveru (enter pro localhost): ")
if not HOST:
    HOST = '127.0.0.1'
PORT = 65432
WIDTH, HEIGHT = 800, 600
PLAYER_SIZE = 20
BG_COLOR = (30, 30, 30)
PLAYER_COLOR = (0, 255, 0)
ENEMY_COLOR = (255, 0, 0)
BULLET_COLOR = (255, 255, 0)
FPS = 60

# Inicializace Pygame
pygame.init()

# Získání přezdívky
# Jednoduchý input v konzoli před spuštěním okna (pro zjednodušení)
nickname = input("Zadej svůj nick: ")
if not nickname:
    nickname = "Student"

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption(f"UDP Střílečka - {nickname}")
clock = pygame.time.Clock()
font = pygame.font.SysFont("Arial", 18)

# --- ÚKOL 1: Inicializace UDP socketu ---
# 1. Vytvořte UDP socket (socket.AF_INET, socket.SOCK_DGRAM)
# 2. Nastavte ho na neblokující režim: socket.setblocking(False)
client_socket = None # TODO: Zde doplňte kód

# Helper pro vykreslování
def draw_player(surface, x, y, angle, color, label=None):
    # Vykreslení trojúhelníku rotovaného podle úhlu
    rad = math.radians(angle)
    # Body trojúhelníku
    tip_x = x + math.cos(rad) * PLAYER_SIZE
    tip_y = y + math.sin(rad) * PLAYER_SIZE
    
    left_x = x + math.cos(rad + 2.5) * PLAYER_SIZE
    left_y = y + math.sin(rad + 2.5) * PLAYER_SIZE
    
    right_x = x + math.cos(rad - 2.5) * PLAYER_SIZE
    right_y = y + math.sin(rad - 2.5) * PLAYER_SIZE
    
    pygame.draw.polygon(surface, color, [(tip_x, tip_y), (left_x, left_y), (right_x, right_y)])
    
    if label:
        text = font.render(label, True, (255, 255, 255))
        surface.blit(text, (x - text.get_width() // 2, y - 35))

def main():
    if client_socket is None:
        print("Chyba: Socket není inicializován (ÚKOL 1).")
        return
    running = True
    server_state = {"players": [], "bullets": [], "leaderboard": []}
    
    try:
        while running:
            clock.tick(FPS)
            
            # 1. Zpracování vstupů (Event loop)
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            keys = pygame.key.get_pressed()
            
            # Sběr inputů
            inputs = {
                "left": keys[pygame.K_LEFT] or keys[pygame.K_a],
                "right": keys[pygame.K_RIGHT] or keys[pygame.K_d],
                "up": keys[pygame.K_UP] or keys[pygame.K_w],
                "down": keys[pygame.K_DOWN] or keys[pygame.K_s],
                "shoot": keys[pygame.K_SPACE]
            }

            # --- ÚKOL 2: Odeslání dat na server ---
            # 1. Vytvořte slovník `data`, který bude obsahovat klíče:
            #    "keys": inputs (to je ten slovník výše)
            #    "nickname": nickname (vaše přezdívka)
            # 2. Převeďte slovník na JSON: json.dumps(data)
            # 3. Převeďte JSON string na bytes: .encode('utf-8')
            # 4. Odešlete pomocí client_socket.sendto(...) na adresu (HOST, PORT)
            
            # TODO: Zde doplňte kód pro odeslání

            # --- ÚKOL 3: Příjem dat ze serveru ---
            # 1. Zkuste přijmout data v cyklu `while True` (aby se přečetla celá fronta)
            # 2. Použijte client_socket.recvfrom(4096)
            # 3. Dekódujte data z bytes na string (.decode('utf-8'))
            # 4. Načtěte JSON do proměnné `server_state`
            # 5. Ošetřete výjimky BlockingIOError (žádná data) a JSONDecodeError (špatná data)
            
            try:
                # TODO: Zde doplňte kód pro příjem
                pass 
            except BlockingIOError:
                pass
            except json.JSONDecodeError:
                pass
            except Exception as e:
                print(f"Chyba sítě: {e}")

            # 4. Vykreslování
            screen.fill(BG_COLOR)

            # Vykreslení hráčů ze serveru
            found_me = False
            my_dead_timer = 0
            
            for p in server_state.get("players", []):
                is_dead = p.get("is_dead", False)
                label = p.get("nickname", "Unknown")
                is_me = (label == nickname)
                
                # Pokud je hráč mrtvý, nevykreslujeme ho
                if is_dead:
                    if is_me:
                        my_dead_timer = p.get("respawn_in", 0)
                        found_me = True
                    continue
                
                color = PLAYER_COLOR if is_me else ENEMY_COLOR
                draw_player(screen, p["x"], p["y"], p["angle"], color, label)
                if is_me:
                    found_me = True
            
            # UI: Respawn Timer
            if my_dead_timer > 0:
                txt = f"RESPAWN IN {my_dead_timer:.1f}s"
                surf = font.render(txt, True, (255, 0, 0))
                # Center screen
                screen.blit(surf, (WIDTH//2 - surf.get_width()//2, HEIGHT//2 - surf.get_height()//2))
            
            if not found_me:
                # Pokud mě server neposílá (jsem mrtvý nebo odpojený), můžu vypsat info
                pass

            # Vykreslení kulek
            for b in server_state.get("bullets", []):
                pygame.draw.circle(screen, BULLET_COLOR, (int(b["x"]), int(b["y"])), 3)

            # Vykreslení Leaderboardu (vlevo nahoře)
            y_off = 10
            lb_title = font.render("--- SCOREBOARD ---", True, (255, 215, 0))
            screen.blit(lb_title, (10, y_off))
            y_off += 25
            
            for entry in server_state.get("leaderboard", []):
                # entry: {nickname, kills, deaths, ratio}
                text = f"{entry['nickname']}: {entry['kills']}K / {entry['deaths']}D"
                surf = font.render(text, True, (200, 200, 200))
                screen.blit(surf, (10, y_off))
                y_off += 20

            pygame.display.flip()

    finally:
        # --- ÚKOL 4 (Bonus): Odeslání odpojení ---
        # Při ukončení (finally blok) pošlete zprávu: {"cmd": "disconnect"}
        # Tím serveru řeknete, aby vás hned smazal.
        print("Ukončuji...")
        # TODO: Zde doplňte kód pro odpojení
        
        pygame.quit()
        sys.exit()

if __name__ == "__main__":
    main()
