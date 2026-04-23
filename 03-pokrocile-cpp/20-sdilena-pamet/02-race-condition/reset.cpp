/*
 * RESET UTILITY
 * Slouží k vytvoření/vynulování sdílené paměti pro demonstraci Race Condition.
 * Spusťte toto PŘED spuštěním 'racer'.
 */

#include <iostream>
#include <cstring>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <unistd.h>
#endif

// Struktura, kterou budeme sdílet
struct SdilenaData {
    int pocitadlo;
};

int main() {
    const char* nazev = "/demo_race_condition";
    const int velikost = sizeof(SdilenaData);
    SdilenaData* data = nullptr;

#ifdef _WIN32
    // Windows: Local\ prefix pro session namespace
    HANDLE hMap = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, velikost, "Local\\DemoRace");
    if (!hMap) { std::cerr << "Chyba CreateFileMapping\n"; return 1; }
    data = (SdilenaData*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, velikost);
#else
    // Linux
    int fd = shm_open(nazev, O_CREAT | O_RDWR, 0666);
    if (fd == -1) { perror("shm_open"); return 1; }
    ftruncate(fd, velikost);
    data = (SdilenaData*)mmap(0, velikost, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
#endif

    // --- RESET ---
    std::cout << "Nuluji pocitadlo ve sdilene pameti..." << std::endl;
    data->pocitadlo = 0;
    std::cout << "Hotovo. Pocitadlo = " << data->pocitadlo << std::endl;
    std::cout << "Nyni spustte 'racer' ve dvou a vice terminalech." << std::endl;

    // Na Linuxu nevoláme shm_unlink, aby paměť zůstala pro racery
    return 0;
}