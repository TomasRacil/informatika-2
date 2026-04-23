/*
 * UDP SERVER
 * * Rozdíly oproti TCP:
 * - Používáme SOCK_DGRAM (datagramy).
 * - Není zde žádný listen() ani accept().
 * - Neudržuje se trvalé spojení. Server prostě "čeká na balíček".
 * - Používáme recvfrom() a sendto(), které obsahují adresu protistrany v parametrech.
 */

#include <iostream>
#include <cstring>
#include <vector>

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
    #define SOCKET_ERROR -1
#endif

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) return 1;
#endif

    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr; // cli_addr bude uchovávat adresu odesílatele

    // 1. Vytvoření socketu
    // SOCK_DGRAM = UDP (User Datagram Protocol)
    // Nespolehlivý, ale rychlý přenos.
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed");
        return 1;
    }

    // 2. Bind - obsazení portu
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; 
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    std::cout << "UDP Server bezi na portu " << PORT << "..." << std::endl;

    while (true) {
        socklen_t len = sizeof(cli_addr); 

        std::cout << "Cekam na data..." << std::endl;
        
        // 3. Čekání na data (recvfrom)
        // DŮLEŽITÉ: Poslední dva parametry (&cli_addr, &len) jsou klíčové.
        // Funkce do nich zapíše, KDO nám data poslal (IP a Port).
        // Bez toho bychom nevěděli, kam poslat odpověď.
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cli_addr, &len);
        
        if (n > 0) {
            buffer[n] = '\0'; // Ukončení řetězce
            
            // Pro výpis si převedeme binární IP na text
            char clientIp[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &cli_addr.sin_addr, clientIp, INET_ADDRSTRLEN);

            std::cout << "Prijato od [" << clientIp << ":" << ntohs(cli_addr.sin_port) << "]: " << buffer << std::endl;

            // 4. Odpověď (sendto)
            // Použijeme získanou adresu 'cli_addr' k odeslání odpovědi zpět.
            const char *msg = "Zprava prijata (UDP)";
            sendto(sockfd, msg, strlen(msg), 0, (const struct sockaddr *)&cli_addr, len);
        }
    }

    CLOSE_SOCKET(sockfd);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}