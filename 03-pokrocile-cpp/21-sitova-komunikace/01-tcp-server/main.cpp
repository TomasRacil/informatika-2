/*
 * TCP SERVER
 * * Tento program demonstruje vytvoření jednoduchého serveru, který:
 * 1. Otevře komunikační kanál (socket).
 * 2. Naváže ho na konkrétní port (8080).
 * 3. Čeká na příchozí spojení od klienta.
 * 4. Přijme zprávu a odešle odpověď.
 * * Kód je psán multiplatformně (funguje na Windows i Linuxu/macOS).
 */

#include <iostream>
#include <cstring> // pro funkce jako memset, strlen

// --- Multiplatformní rozcestník ---
// Windows používá knihovnu Winsock (winsock2.h), zatímco Linux/macOS
// používá standardní POSIX knihovny (sys/socket.h).
#ifdef _WIN32
    #include <winsock2.h> // Hlavní hlavička pro sítě na Windows
    #include <ws2tcpip.h> // Moderní funkce pro práci s IP adresami
    #pragma comment(lib, "ws2_32.lib") // Říká kompilátoru (MSVC), aby přilinkoval knihovnu ws2_32
    
    // Sjednocení názvů funkcí: Windows používá closesocket(), Linux close()
    #define CLOSE_SOCKET closesocket
    // Windows používá 'int' pro délku adresy, Linux 'socklen_t'
    typedef int socklen_t;
#else
    #include <unistd.h>     // Obsahuje funkci close()
    #include <sys/socket.h> // Hlavní funkce: socket, bind, listen...
    #include <netinet/in.h> // Definice struktur pro adresy (sockaddr_in)
    
    #define CLOSE_SOCKET close
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

int main() {
    // -------------------------------------------------------------------------
    // KROK 0: Inicializace knihovny (Pouze pro Windows)
    // -------------------------------------------------------------------------
#ifdef _WIN32
    WSADATA wsaData;
    // WSAStartup načte knihovnu Winsock DLL. 
    // MAKEWORD(2, 2) žádá o verzi 2.2.
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Selhalo WSAStartup (chyba inicializace Winsock)." << std::endl;
        return 1;
    }
#endif

    int server_fd, new_socket;
    struct sockaddr_in address; // Struktura uchovávající IP a Port
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0}; // Buffer pro příchozí data
    const char* hello = "Ahoj od serveru (Multiplatform C++)!";

    // -------------------------------------------------------------------------
    // KROK 1: Vytvoření socketu
    // -------------------------------------------------------------------------
    // AF_INET      = IPv4 protokol (pro IPv6 by bylo AF_INET6)
    // SOCK_STREAM  = TCP protokol (spojovaný, spolehlivý tok dat)
    // 0            = Automaticky vybrat protokol (IPPROTO_TCP)
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket failed"); // Vypíše chybovou hlášku systému
        return 1;
    }

    // -------------------------------------------------------------------------
    // KROK 2: Nastavení vlastností socketu (Volitelné, ale doporučené)
    // -------------------------------------------------------------------------
    // Povoluje znovupoužití adresy/portu (SO_REUSEADDR). 
    // Bez toho by po restartu serveru mohl OS hlásit "Address already in use" ještě několik minut.
#ifdef _WIN32
    // Windows vyžaduje přetypování na (const char*)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt))) {
#else
    // Linux podporuje i SO_REUSEPORT pro load balancing (není nutné)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
#endif
        perror("setsockopt");
        return 1;
    }

    // -------------------------------------------------------------------------
    // KROK 3: Bind - Navázání socketu na IP a Port
    // -------------------------------------------------------------------------
    address.sin_family = AF_INET;
    // INADDR_ANY = Server bude naslouchat na všech síťových kartách (Wi-Fi, Ethernet, localhost...)
    address.sin_addr.s_addr = INADDR_ANY; 
    // htons = "Host TO Network Short". Převádí číslo portu (např. 8080) 
    // z formátu PC (Little Endian) na síťový formát (Big Endian).
    address.sin_port = htons(8080);

    // Propojení deskriptoru socketu s nastavenou adresou
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // -------------------------------------------------------------------------
    // KROK 4: Listen - Přepnutí do pasivního režimu
    // -------------------------------------------------------------------------
    // Číslo 3 (backlog) určuje maximální délku fronty čekajících spojení.
    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        return 1;
    }

    std::cout << "Server bezi na portu 8080... Cekam na pripojeni klienta." << std::endl;

    // -------------------------------------------------------------------------
    // KROK 5: Accept - Přijetí spojení
    // -------------------------------------------------------------------------
    // Tato funkce BLOKUJE program (uspí ho), dokud se někdo nepřipojí.
    // Jakmile se klient připojí, vytvoří se NOVÝ socket (new_socket) určený 
    // pouze pro komunikaci s tímto konkrétním klientem. Původní (server_fd) naslouchá dál.
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept");
        return 1;
    }

    std::cout << "Klient uspesne pripojen!" << std::endl;

    // -------------------------------------------------------------------------
    // KROK 6: Komunikace (recv / send)
    // -------------------------------------------------------------------------
    // recv() čte data ze socketu do bufferu. Vrací počet přečtených bajtů.
    int valread = recv(new_socket, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Zprava od klienta: " << buffer << std::endl;
    }

    // send() posílá data klientovi.
    send(new_socket, hello, strlen(hello), 0);
    std::cout << "Odpoved odeslana." << std::endl;

    // -------------------------------------------------------------------------
    // KROK 7: Úklid
    // -------------------------------------------------------------------------
    CLOSE_SOCKET(new_socket); // Zavřeme spojení s klientem
    CLOSE_SOCKET(server_fd);  // Zavřeme naslouchající socket

#ifdef _WIN32
    WSACleanup(); // Uvolnění Winsock knihovny
#endif

    return 0;
}