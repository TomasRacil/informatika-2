#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "logger.h"

class Server
{
private:
    Logger *logger;

    std::vector<std::string> urovne = {"INFO", "WARNING", "ERROR"};
    std::vector<std::string> objekty = {"Databaze", "Server", "System"};

    std::vector<std::string> zpravy = {
        "Start procesu", "Uzivatel prihlasen", "Zaloha dokoncena",
        "Vysoka odezva", "Nizka pamet", "Neznamy pozadavek",
        "Spojeni selhalo", "Segfault", "Disk plny"};

public:
    Server(Logger *l)
    {
        logger = l;
    }

    void run(int pocetUdalosti)
    {
        std::cout << "Server bezi a generuje " << pocetUdalosti << " logu..." << std::endl;

        for (int i = 0; i < pocetUdalosti; i++)
        {
            int indexUrovne = rand() % urovne.size();
            int indexObjektu = rand() % objekty.size();
            int zacatekSekce = indexUrovne * 3;
            int posun = rand() % 3;
            int indexZpravy = zacatekSekce + posun;
            logger->log(urovne[indexUrovne], objekty[indexObjektu], zpravy[indexZpravy]);
        }

        std::cout << "Generovani dokonceno." << std::endl;
    }
};

int main()
{
    srand(time(0));

    Logger mujLogger("server.log");

    Server mujServer(&mujLogger);

    mujServer.run(50);

    return 0;
}