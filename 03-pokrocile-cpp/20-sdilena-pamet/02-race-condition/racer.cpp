/*
 * RACER (Chybná verze)
 * Tento program se připojí ke sdílené paměti a pokusí se zvýšit počítadlo 100 000x.
 * Protože nepoužívá žádný zámek (Mutex/Semafor), při běhu více instancí dojde k chybě souběhu.
 */

#include <iostream>
#include <thread> // Jen pro sleep
#include <vector>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <unistd.h>
#endif

struct SdilenaData {
    int pocitadlo;
};

int main() {
    const int POCET_ITERACI = 100000;
    SdilenaData* data = nullptr;

#ifdef _WIN32
    HANDLE hMap = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "Local\\DemoRace");
    if (!hMap) { std::cerr << "Spustte nejdrive 'reset'!\n"; return 1; }
    data = (SdilenaData*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SdilenaData));
#else
    int fd = shm_open("/demo_race_condition", O_RDWR, 0666);
    if (fd == -1) { std::cerr << "Spustte nejdrive 'reset'!\n"; return 1; }
    data = (SdilenaData*)mmap(0, sizeof(SdilenaData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#endif

    std::cout << "Start! Inkrementuji " << POCET_ITERACI << "x..." << std::endl;

    for (int i = 0; i < POCET_ITERACI; ++i) {
        // --- KRITICKÁ SEKCE (BEZ OCHRANY!) ---
        // Zde dochází k Race Condition.
        // Operace ++ není atomická (Read-Modify-Write).
        data->pocitadlo++;
    }

    std::cout << "Hotovo. Aktualni hodnota ve sdilene pameti: " << data->pocitadlo << std::endl;
    return 0;
}