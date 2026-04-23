/*
 * SAFE RACER (Bezpečná verze)
 * Stejný úkol jako racer.cpp, ale používá Pojmenovaný Semafor k synchronizaci.
 * I když poběží 10 instancí najednou, výsledek bude správný.
 */

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <unistd.h>
    #include <semaphore.h> // POSIX semafory
#endif

struct SdilenaData {
    int pocitadlo;
};

int main() {
    const int POCET_ITERACI = 100000;
    SdilenaData* data = nullptr;

    // 1. Připojení ke sdílené paměti (stejné jako minule)
#ifdef _WIN32
    HANDLE hMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "Local\\DemoRace");
    if (!hMap) { std::cerr << "Spustte nejdrive 'reset' (ze slozky 02)!\n"; return 1; }
    data = (SdilenaData*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SdilenaData));
#else
    int fd = shm_open("/demo_race_condition", O_RDWR, 0666);
    if (fd == -1) { std::cerr << "Spustte nejdrive 'reset' (ze slozky 02)!\n"; return 1; }
    data = (SdilenaData*)mmap(0, sizeof(SdilenaData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#endif

    // 2. Otevření/Vytvoření Pojmenovaného Semaforu
    // Tento semafor slouží jako Mutex (kapacita 1).
#ifdef _WIN32
    // Windows: CreateSemaphore (pokud existuje, vrátí handle na něj)
    // 1 = InitialCount (odemčeno), 1 = MaxCount
    HANDLE semafor = CreateSemaphoreA(NULL, 1, 1, "Local\\MujBezpecnySemafor");
    if (!semafor) { std::cerr << "Chyba semaforu\n"; return 1; }
#else
    // Linux: sem_open
    // 1 = Initial value (odemčeno)
    sem_t* semafor = sem_open("/muj_bezpecny_semafor", O_CREAT, 0666, 1);
    if (semafor == SEM_FAILED) { perror("sem_open"); return 1; }
#endif

    std::cout << "Start! (Bezpecne)..." << std::endl;

    for (int i = 0; i < POCET_ITERACI; ++i) {
        
        // --- LOCK (WAIT) ---
        // Požádáme OS o vstup. Pokud tam je jiný proces, zde se zastavíme a čekáme.
#ifdef _WIN32
        WaitForSingleObject(semafor, INFINITE);
#else
        sem_wait(semafor);
#endif

        // --- KRITICKÁ SEKCE ---
        // Teď jsme tu sami. Můžeme bezpečně číst a zapisovat.
        data->pocitadlo++;

        // --- UNLOCK (SIGNAL/POST) ---
        // Uvolníme zámek pro další procesy.
#ifdef _WIN32
        ReleaseSemaphore(semafor, 1, NULL);
#else
        sem_post(semafor);
#endif
    }

    std::cout << "Hotovo. Aktualni hodnota: " << data->pocitadlo << std::endl;

#ifdef _WIN32
    CloseHandle(semafor);
#else
    sem_close(semafor);
#endif

    return 0;
}