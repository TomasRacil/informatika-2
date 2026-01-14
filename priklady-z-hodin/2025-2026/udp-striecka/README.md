# UDP Střílečka - Zadání

Tento projekt implementuje jednoduchou multiplayerovou hru, kde se hráči pohybují jako trojúhelníčky a střílejí po sobě. Komunikace probíhá přes UDP protokol.

## Struktura projektu

- `server.py`: Serverová část hry.
  - Spravuje pozice hráčů a kulek.
  - Odesílá všem klientům stav hry (broadcast).
  - Řeší kolize (zásahy).
  - **Nově:** Zobrazuje stav hry v okně (Pygame).
- `client_student.py`: Nekompletní klient s úkoly k doplnění.

## Jak spustit

1. **Spuštění serveru**:
   Otevřete terminál a spusťte:
   ```bash
   python server.py
   ```
   Server bude naslouchat na `127.0.0.1:65432`.

2. **Spuštění klienta**:
   Otevřete nový terminál pro každého klienta a spusťte:
   ```bash
   python client_student.py
   ```
   
   *Při spuštění klienta budete vyzváni k zadání ip adresy serveru (defaultní  127.0.0.1) a přezdívky.*

## Zadání pro studenty

Otevřete soubor `client_student.py` a doplňte chybějící části kódu označené komentáři `# TODO`:

1.  **UDP Socket**: Vytvořte soket (`socket.AF_INET`, `socket.SOCK_DGRAM`) a nastavte ho na neblokující režim.
2.  **Odesílání**: Vytvořte balíček dat s klíči `keys` (vstupy) a `nickname` a pošlete ho na server.
3.  **Příjem**: Přijměte data ze serveru (musíte číst ve smyčce `while True`), dekódujte JSON a aktualizujte stav hry.
4.  **Odpojení (Bonus)**: Při ukončení hry pošlete serveru zprávu `{"cmd": "disconnect"}`.

## Komunikační Protokol (JSON)

**Klient -> Server**
```json
{
  "nickname": "Pepa",
  "keys": {
    "left": false,
    "right": true,
    "up": false,
    "down": false,
    "shoot": true
  }
}
```
*Pro odpojení:* `{"cmd": "disconnect"}`

**Server -> Klient**
```json
{
  "players": [
    {"x": 100, "y": 200, "angle": 90, "nickname": "Pepa", "is_dead": false, "respawn_in": 0},
    ...
  ],
  "bullets": [ ... ],
  "leaderboard": [ ... ]
}
```

## Síť a Firewall

Aby se mohli připojit studenti z jiných počítačů, musíte povolit port **65432** ve Firewallu na počítači, kde běží `server.py`.

*   **Windows**: Pravým tlačítkem klikněte na `allow_firewall.ps1` a zvolte "Spustit pomocí prostředí PowerShell" (Run with PowerShell). Potvrďte práva administrátora. Je potřeba nastavit execution policy na Unrestricted pomocí `Set-ExecutionPolicy Unrestricted`.
*   **Linux**: Spusťte `bash allow_firewall.sh` možná bude potřeba změnit práva souboru pomocí `chmod +x allow_firewall.sh`.

## Ovládání a Pravidla

- **Šipky** nebo **WASD**: Pohyb a otáčení.
- **Mezerník**: Střelba.
- **Pravidla**:
  - Za zásah jiného hráče získáváte **KILL**.
  - Pokud jste zasaženi, získáváte **DEATH** a jste respawnováni na střed mapy.
  - Vlevo na obrazovce se zobrazuje **Scoreboard** seřazený podle poměru Kills/Deaths.
- Server běží neustále, i když se všichni odpojí.

## Požadavky

- Python 3.x
- Knihovna `pygame` (`pip install pygame`)
- Knihovna `socket`, `json` (součást Pythonu)
