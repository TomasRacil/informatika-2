/*
 * TCP KLIENT
 * * Tento program se pokusí připojit k běžícímu serveru.
 * 1. Vytvoří socket.
 * 2. Převede IP adresu a Port.
 * 3. Zavolá connect() pro navázání spojení.
 * 4. Pošle zprávu a čeká na odpověď.
 */

#include <iostream>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define CLOSE_SOCKET closesocket
#else
    #include <unistd.h>
    #include <sys/socket.h>
    #include <arpa/inet.h> // inet_pton
    #define CLOSE_SOCKET close
    #define INVALID_SOCKET -1
#endif

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return -1;
    }
#endif

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char* hello = "Ahoj od klienta!";
    char buffer[1024] = {0};

    // 1. Vytvoření socketu
    // Stejné jako u serveru: AF_INET (IPv4), SOCK_STREAM (TCP)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cout << "\n Socket creation error \n";
        return -1;
    }

    // 2. Příprava adresy serveru
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080); // Port, kde běží server

    // inet_pton = "Presentation TO Network".
    // Převádí textovou IP adresu ("127.0.0.1") na binární formát, kterému rozumí síťová karta.
    // Pokud se server nespouští lokálně, změňte "127.0.0.1" na IP adresu serveru.
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    // 3. Connect - Navázání spojení (3-Way Handshake)
    // Pokusí se kontaktovat server. Pokud server neběží, funkce selže.
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed (bezi server?)\n";
        return -1;
    }

    std::cout << "Pripojeno k serveru!" << std::endl;

    // 4. Odeslání dat
    send(sock, hello, strlen(hello), 0);
    std::cout << "Zprava odeslana serveru." << std::endl;

    // 5. Čekání na odpověď
    // recv() je blokující - program zde čeká, dokud server něco nepošle.
    valread = recv(sock, buffer, 1024, 0);
    if (valread > 0) {
        std::cout << "Odpoved od serveru: " << buffer << std::endl;
    }

    CLOSE_SOCKET(sock);

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}