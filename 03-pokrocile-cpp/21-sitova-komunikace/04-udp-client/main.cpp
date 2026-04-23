/*
 * UDP KLIENT
 * * Tento klient posílá datagramy na server.
 * Všimněte si, že nevoláme connect() (i když to u UDP jde pro nastavení výchozího cíle).
 * Místo toho v každém volání sendto() explicitně říkáme, komu data posíláme.
 */

#include <iostream>
#include <cstring>
#include <string> // std::getline

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
    typedef int socklen_t;
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #define CLOSE_SOCKET close
    #define INVALID_SOCKET -1
#endif

#define PORT 8888
#define SERVER_IP "127.0.0.1"

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return 1;
#endif

    int sockfd;
    char buffer[1024];
    struct sockaddr_in serv_addr;

    // 1. Vytvoření socketu (UDP)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Nastavení adresy cíle (Serveru)
    // Tuto strukturu budeme předávat funkci sendto() při každém odeslání.
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Převod textové IP na binární
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cout << "Neplatna adresa" << std::endl;
        return 1;
    }

    while (true) {
        std::string input;
        std::cout << "Zadej zpravu (nebo 'exit'): ";
        std::getline(std::cin, input);

        if (input == "exit") break;

        // 3. Odeslání dat (sendto)
        // Odesíláme data "naslepo" na adresu serv_addr.
        // Nevíme, jestli server běží nebo poslouchá. UDP nám nedá vědět, pokud se paket ztratí.
        sendto(sockfd, input.c_str(), input.length(), 0, 
               (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
        
        std::cout << "Zprava odeslana." << std::endl;

        // 4. Čekání na odpověď (volitelné)
        // Zde čekáme, zda server něco pošle zpět.
        // Pokud server neodpoví (paket se ztratil), program zde může "zamrznout" navždy.
        // V reálné aplikaci by se zde použil timeout (setsockopt SO_RCVTIMEO).
        socklen_t len = sizeof(serv_addr);
        int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&serv_addr, &len);
        
        if (n > 0) {
            buffer[n] = '\0';
            std::cout << "Server odpovedel: " << buffer << std::endl;
        }
    }

    CLOSE_SOCKET(sockfd);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}