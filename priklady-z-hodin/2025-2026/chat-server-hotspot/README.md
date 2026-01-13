# Úkol: Multithreaded Chat Server

Vítejte u praktického úkolu, který spojuje vaše znalosti **síťové komunikace (sockety)** a **paralelního programování (vlákna)**. 

Cílem je vytvořit funkční **Chatovací Místnost**, kde si může psát celá třída najednou.

---

## Plán práce (Tutoriál)

Postupujte podle jednotlivých fází.

1.  **Design**: Jak to bude fungovat?
2.  **Server**: Mozek operace.
3.  **Klient**: Aplikace pro uživatele.
4.  **Zapojení**: Jak to zprovoznit na síti (Firewall, IP, WSL).

---

## Fáze 0: Příprava a Teorie

Otevřete si materiály, budete je potřebovat pro syntaxi příkazů:
*   **Python**: [Sockety](../../05-pokrocily-python/19-klasicke-sockety/) a [Vlakna a paralelní programování](../../../../05-pokrocily-python/16-vlakna/)
*   **C++**: [Sockety](../../../../03-pokrocile-cpp/20-sitova-komunikace/) a [Vlakna a paralelní programování](../../../../03-pokrocile-cpp/18-vlakna-a-paralelni-programovani/)

---

## Fáze 1: Implementace Serveru

Server je program, který běží na jednom počítači a přeposílá zprávy všem ostatním.

### Krok 1.1: Základní Socket
Vytvořte socket, který naslouchá na **všech síťových rozhraních** (`0.0.0.0`) na portu `12345`.
*   *Tip:* `bind(('0.0.0.0', 12345))`
*   *Tip:* Nezapomeňte na `listen()`.

### Krok 1.2: Evidence klientů
Vytvořte globální seznam (pole/vektor), kam si budete ukládat připojené klienty.
*   Bude to potřeba pro rozesílání zpráv (Broadcast).
*   *Pozor (C++):* Přístup k tomuto seznamu by měl být chráněn mutexem! V Pythonu je GIL, ale pro čistotu návrhu je `Lock` také vhodný.

### Krok 1.3: Smyčka pro přijímání (Main Loop)
V hlavní části programu vytvořte nekonečný cyklus `while True`, který:
1.  Čeká na nového klienta (`accept()`).
2.  Jakmile se někdo připojí:
    *   Vypíše "Připojen: <IP adresa>".
    *   Uloží socket klienta do seznamu klientů.
    *   **Spustí nové vlákno** pro obsluhu tohoto konkrétního klienta (předejte mu socket).

### Krok 1.4: Funkce pro obsluhu klienta (Vlákno)
Tato funkce běží paralelně pro každého uživatele.
1.  V nekonečném cyklu čte data od klienta (`recv()`).
2.  **Pokud přijdou data:**
    *   Projdi seznam všech klientů.
    *   Každému (kromě odesílatele) tuto zprávu pošli (`send()`).
3.  **Pokud data nepřijdou (klient se odpojil):**
    *   Zavři socket.
    *   Odeber klienta ze seznamu.
    *   Ukonči vlákno/funkci.

**Pseudokód Serveru:**
```text
Global List clients

Function HandleClient(client_socket):
    Loop Forever:
        try:
            message = client_socket.Receive()
            If message is empty OR error:
                Break Loop
            
            # Broadcast všem ostatním
            For each c in clients:
                If c != client_socket:
                    c.Send(message)
        catch:
            Break Loop
    
    client_socket.Close()
    Remove client_socket from clients

Function Main:
    server = CreateTCPSocket()
    server.Bind("0.0.0.0", 12345)
    server.Listen()

    Loop Forever:
        client_sock = server.Accept()
        Add client_sock to clients
        StartThread(HandleClient, client_sock)
```

---

## Fáze 2: Implementace Klienta

Klient je složitější v tom, že musí dělat **dvě věci najednou**:
1.  Čekat na zprávy od serveru (aby se vypsaly, když někdo napíše).
2.  Čekat na vstup od uživatele na klávesnici (aby mohl psát).

Proto i klient **musí být multithreaded**!

### Krok 2.1: Připojení
Vytvořte socket a připojte se (`connect()`) na IP adresu serveru (zatím testujte s `127.0.0.1` nebo `localhost`).

### Krok 2.2: Vlákno pro naslouchání (Receiver)
Vytvořte funkci, která:
1.  Běží ve smyčce.
2.  Volá `recv()` na socketu.
3.  Cokoliv přijde, vypíše na obrazovku (`print` / `std::cout`).
4.  Pokud server spojení ukončí, vypíše chybu a ukončí program.

*V hlavním programu toto vlákno nastartujte hned po připojení.*

### Krok 2.3: Smyčka pro odesílání (Sender)
Toto může běžet v hlavním vlákně programu.
1.  V nekonečné smyčce čti vstup z klávesnice (`input()` / `std::cin` / `std::getline`).
2.  Načtený text pošli na server (`send()`).
3.  Pokud uživatel napíše "konec" nebo "exit", ukonči program.

**Pseudokód Klienta:**
```text
Function ReceiveMessages(socket):
    Loop Forever:
        try:
            message = socket.Receive()
            Print message
        catch:
            Print "Connection Lost"
            Break Loop

Function Main:
    socket = CreateTCPSocket()
    socket.Connect("SERVER_IP", 12345)

    # Spustit vlákno pro příjem
    StartThread(ReceiveMessages, socket)

    # Odesílání v hlavním vlákně
    Loop Forever:
        text = ReadInputFromUser()
        If text == "exit": 
            Break Loop
        socket.Send(text)
```

---

## Fáze 3: Nasazení v síti (Networking)

Nyní máte funkční kód. Aby se ale připojil spolužák, musíte opustit bezpečí `localhostu`.

> **Pozor na školní sítě!**
> Veřejné a školní Wi-Fi sítě často obsahují bezpečnostní prvek zvaný **AP Isolation**, který brání zařízením komunikovat přímo mezi sebou. 
>
> **Doporučení:** 
> 1.  Vytvořte si **Hotspot přímo na notebooku**.
> 2.  Nebo použijte **Hotspot na mobilu** a připojte se k němu všichni.
>
> Tím vytvoříte vlastní lokální síť bez omezení. Data se spotřebovávají minimálně.

### Krok 3.1: Zjištění IP Adresy (Server)
Student, který spouští server, musí zjistit svou lokální IP adresu.
*   **Windows**: `ipconfig` (Hledejte Wireless LAN / Wi-Fi -> IPv4 Address).
*   **Linux/Mac**: `ip a` nebo `ifconfig` (Hledejte `wlan0` / `eth0`).

### Krok 3.2: Nastavení Firewallu (Server)
Serverový počítač musí povolit port 12345.

*   **Windows (PowerShell jako Admin)**:
    ```powershell
    New-NetFirewallRule -DisplayName "Chat Server" -Direction Inbound -LocalPort 12345 -Protocol TCP -Action Allow
    ```
    *(Po hodině smazat: `Remove-NetFirewallRule -DisplayName "Chat Server"`)*

*   **Linux**: `sudo ufw allow 12345/tcp`
*   **macOS**: Obvykle vyskočí okno *"Do you want the application python to accept incoming network connections?"* -> Klikněte na **Allow**.

### Krok 3.3: WSL Specifika (Pokud server běží ve WSL)
Pokud spouštíte server v terminálu WSL, je "schovaný" za virtuální sítí.

1.  **Doporučeno**: Spusťte server raději přes `cmd.exe` nebo `powershell.exe` přímo ve Windows.
2.  **Nutnost WSL**: Musíte nastavit **Port Forwarding**.
    *   Zjistěte IP WSL: `ip addr show eth0 | grep inet` (např. 172.x.x.x)
    *   PowerShell (Admin):
        ```powershell
        netsh interface portproxy add v4tov4 listenaddress=0.0.0.0 listenport=12345 connectaddress=<IP_WSL> connectport=12345
        ```

---

## Fáze 4: Testování
1.  Server běží na počítači A (IP např. `192.168.1.50`).
2.  Klient na počítači B se připojuje na `192.168.1.50`.
3.  Klient na počítači C se připojuje na `192.168.1.50`.
4.  B napíše zprávu -> C by ji měl vidět (a A v logu také).

**Bonusové úkoly:**
*   **Přezdívky**: První zpráva po připojení se bere jako jméno.
*   **Identity**: Před každou zprávu server přidá `<Pepa>: Ahoj`.
*   **Barvy**: Použijte ANSI kódy pro barevný výstup v terminálu.
