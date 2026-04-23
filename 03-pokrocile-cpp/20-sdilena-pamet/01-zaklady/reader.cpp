/*
 * SHARED MEMORY - READER (Čtenář)
 * * Tento program:
 * 1. Pokusí se najít existující sdílenou paměť vytvořenou Writerem.
 * 2. Namapuje si ji (pouze pro čtení).
 * 3. Přečte data a vypíše je.
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

int main() {
    const int velikost = 4096;
    void* ptr = nullptr;

#ifdef _WIN32
    // -------------------------------------------------------------------------
    // WINDOWS
    // -------------------------------------------------------------------------
    const char* nazev = "Local\\MojeSdilenaPamet"; // Musí být stejné jako ve Writeru

    // 1. Otevření existujícího mappingu
    // OpenFileMapping na rozdíl od CreateFileMapping nevytváří novou paměť.
    // Pokud neexistuje, vrátí NULL.
    HANDLE hMapFile = OpenFileMappingA(
        FILE_MAP_READ, // Chceme pouze číst
        FALSE,         // Dědičnost handlu (nepodstatné)
        nazev);        // Jméno
    
    if (hMapFile == NULL) {
        std::cerr << "Chyba: Nelze otevrit sdilenou pamet." << std::endl;
        std::cerr << "Tip: Bezi program 'writer'?" << std::endl;
        return 1;
    }

    // 2. Mapování
    ptr = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, velikost);
    
    if (ptr == NULL) {
        std::cerr << "Chyba MapViewOfFile" << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

#else
    // -------------------------------------------------------------------------
    // LINUX / POSIX
    // -------------------------------------------------------------------------
    const char* nazev = "/moje_sdilena_pamet";

    // 1. Otevření objektu
    // O_RDONLY = Otevřít pouze pro čtení.
    // Nepoužíváme O_CREAT, protože chceme selhat, pokud Writer neběží.
    int shm_fd = shm_open(nazev, O_RDONLY, 0666);
    if (shm_fd == -1) {
        std::cerr << "Chyba: Nelze otevrit sdilenou pamet (shm_open failed)." << std::endl;
        std::cerr << "Tip: Bezi program 'writer'?" << std::endl;
        return 1;
    }

    // 2. Mapování (mmap)
    // PROT_READ = Pouze právo číst. Pokus o zápis by shodil program (Segmentation Fault).
    ptr = mmap(0, velikost, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
#endif

    // -------------------------------------------------------------------------
    // SPOLEČNÁ ČÁST
    // -------------------------------------------------------------------------
    
    std::cout << "[Reader] Pamet uspesne pripojena. Adresa: " << ptr << std::endl;
    
    // Čtení dat - prostě přečteme data z ukazatele, jako by to byl string
    // (Předpokládáme, že tam Writer uložil text ukončený nulou)
    std::cout << "[Reader] Obsah pameti: " << (char*)ptr << std::endl;

    // -------------------------------------------------------------------------
    // Úklid
    // -------------------------------------------------------------------------
#ifdef _WIN32
    UnmapViewOfFile(ptr);
    CloseHandle(hMapFile);
#else
    munmap(ptr, velikost);
    close(shm_fd);
    // Poznámka: Reader obvykle nevolá shm_unlink(). 
    // To dělá ten, kdo paměť vytvořil (Writer), nebo ten, kdo končí poslední.
#endif

    return 0;
}