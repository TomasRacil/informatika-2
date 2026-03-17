# **20 - Síťová komunikace (Sockets)**

Programování sítě nám umožňuje propojit aplikace běžící na různých počítačích (nebo různých procesech).  
V C++ používáme nízkoúrovňové rozhraní zvané Berkeley Sockets (nebo Winsock na Windows).

## **1. Základní pojmy**

### **Socket**

Představte si Socket jako **dveře**, kterými data odcházejí z vašeho programu do sítě a přicházejí zpět.

* V systému je reprezentován jako **File Descriptor** (celé číslo, např. 3).  
* Operační systém se stará o detaily (síťová karta, drivery). My jen čteme/zapisujeme do "souboru".

### **Adresování: IP a Port**

Abychom doručili data správné aplikaci, potřebujeme dvě informace:

1. **IP Adresa:** Identifikuje počítač v síti (např. `192.168.1.15` nebo `127.0.0.1` pro localhost).  
2. **Port:** Identifikuje konkrétní běžící aplikaci na tomto počítači (např. Web běží na 80, Minecraft na 25565).

### **Endianita (Network Byte Order)**

Počítače ukládají čísla v paměti různě:

* **Little-Endian (Intel/AMD x86):** Nejméně významný bajt první.  
* **Big-Endian (Síťový standard):** Nejvíce významný bajt první.

Pokud pošlete číslo `1000` (binárně `00000011 11101000`) z Intel počítače do sítě bez úpravy, dorazí pozpátku! Proto musíme používat konverzní funkce:

* `htons()` (Host to Network Short) – pro porty.  
* `htonl()` (Host to Network Long) – pro IP adresy.

## **2. Protokoly: TCP vs. UDP**

V transportní vrstvě se rozhodujeme mezi dvěma přístupy.

### **A. TCP (Transmission Control Protocol)**

1. **Spojovaný:** Musíte navázat spojení, než zahájíte komunikaci.  
2. **Spolehlivý:** Protokol garantuje, že data dorazí **všechna** a ve **správném pořadí**. Pokud se paket ztratí, pošle se znovu.  
3. **Stream:** Data tečou jako proud vody. Neexistují "hranice" zpráv (odeslání 2x "Ahoj" může přijít jako jedno "AhojAhoj").  
4. **Použití:** Web (HTTP), Email, Chat, Přenos souborů.

**3-Way Handshake (Navázání spojení):**

1. Klient -> `SYN` -> Server ("Chci se spojit")  
2. Server -> `SYN-ACK` -> Klient ("Slyším a souhlasím")  
3. Klient -> `ACK` -> Server ("OK, začínáme")

### **B. UDP (User Datagram Protocol)**

1. **Nespojovaný:** Pošlete data do sítě na cílovou adresu. Nevíte, jestli tam je někdo, kdo poslouchá.  
2. **Nespolehlivý:** Pakety se mohou ztratit, přijít dvakrát nebo v jiném pořadí. Aplikace to musí řešit sama.  
3. **Datagramy:** Data chodí v balíčcích. Co odešlete jedním `sendto`, to se přečte jedním `recvfrom`.  
4. **Rychlý:** Žádné zdržování handshakem nebo čekáním na potvrzení.  
5. **Použití:** Streamování videa, Online FPS hry (poloha hráčů), DNS.

## **3. Client-Server model v kódu**

### **TCP Flow**

* **Server:** `socket()` -> `bind()` -> `listen()` -> `accept()` -> `recv/send`.  
* **Klient:** `socket()` -> `connect()` -> `send/recv`.

### **UDP Flow**

* **Server:** `socket()` -> `bind()` -> `recvfrom()` -> `sendto()`.  
* **Klient:** `socket()` -> `sendto()` -> `recvfrom()`.
---
## **Cvičení**

### **1. Jednoduchý Chat**
Napište dvě aplikace:
1. **Server**: Vytvoří socket, nabinduje ho na port 8080 a přepne do naslouchání (`listen`). V nekonečném cyklu přijímá spojení (`accept`). Jakmile se klient připojí, přečte data (`recv`) a vypíše je na obrazovku.
2. **Klient**: Připojí se k serveru na localhost:8080. Čte vstup od uživatele (`std::cin`) a posílá ho na server (`send`).

### **2. Vylepšení (Echo)**
Upravte server tak, aby přijaté zprávy poslal **zpátky** klientovi (Echo).
Upravte klienta tak, aby po odeslání zprávy čekal na odpověď a vypsal ji ("Server odpověděl: ...").
