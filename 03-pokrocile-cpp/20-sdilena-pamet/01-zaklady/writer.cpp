/*
 * SHARED MEMORY - WRITER (Zapisovatel)
 * * Tento program:
 * 1. Vytvoří (alokuje) kus sdílené paměti v operačním systému.
 * 2. Namapuje si ji do svého adresního prostoru jako pole charů.
 * 3. Zapíše do ní zprávu.
 * 4. Čeká, dokud uživatel neukončí program (aby paměť nezmizela, než si ji Reader přečte).
 */

#include <iostream>
#include <cstring> // memcpy, strlen

// --- Multiplatformní hlavičky ---
#ifdef _WIN32
    #include <windows.h> // API pro Windows (CreateFileMapping, MapViewOfFile)
#else
    #include <fcntl.h>      // Konstanty O_CREAT, O_RDWR
    #include <sys/mman.h>   // Hlavní funkce: shm_open, mmap
    #include <unistd.h>     // ftruncate, close
#endif

int main() {
    const int velikost = 4096; // Velikost sdílené paměti (4 KB je obvykle velikost jedné stránky paměti)
    const char* zprava = "Ahoj! Toto je zprava ze sdilene pameti prenesena bleskovou rychlosti.";
    
    // Ukazatel, přes který budeme přistupovat ke sdílené paměti
    void* ptr = nullptr; 

#ifdef _WIN32
    // -------------------------------------------------------------------------
    // WINDOWS IMPLEMENTACE
    // -------------------------------------------------------------------------
    const char* nazev = "Local\\MojeSdilenaPamet"; // Prefix "Local\" omezuje viditelnost na aktuálního uživatele

    // 1. Vytvoření objektu "File Mapping"
    // Windows spravuje sdílenou paměť podobně jako soubory. 
    // INVALID_HANDLE_VALUE znamená "nepoužívej fyzický soubor na disku, ale RAM".
    HANDLE hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,   
        NULL,                   // Výchozí zabezpečení
        PAGE_READWRITE,         // Povolujeme čtení i zápis
        0,                      // Velikost (High DWORD) - pro soubory > 4GB
        velikost,               // Velikost (Low DWORD)
        nazev);                 // Jméno, podle kterého ji najde Reader

    if (hMapFile == NULL) {
        std::cerr << "Chyba CreateFileMapping: " << GetLastError() << std::endl;
        return 1;
    }

    // 2. Mapování do paměti procesu
    // Získáme ukazatel (ptr), který můžeme používat jako běžné pole.
    ptr = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, velikost);
    
    if (ptr == NULL) {
        std::cerr << "Chyba MapViewOfFile" << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

#else
    // -------------------------------------------------------------------------
    // LINUX / POSIX IMPLEMENTACE
    // -------------------------------------------------------------------------
    const char* nazev = "/moje_sdilena_pamet"; // Jméno musí začínat lomítkem

    // 1. Vytvoření objektu sdílené paměti
    // shm_open vytvoří "soubor" v /dev/shm/
    // O_CREAT = vytvořit, pokud neexistuje
    // O_RDWR  = otevřít pro čtení i zápis
    // 0666    = práva (číst/zapisovat může kdokoliv)
    int shm_fd = shm_open(nazev, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }

    // 2. Nastavení velikosti
    // Nově vytvořený objekt má velikost 0. Musíme ho "nafouknout".
    if (ftruncate(shm_fd, velikost) == -1) {
        perror("ftruncate");
        return 1;
    }

    // 3. Mapování do paměti (mmap)
    // PROT_WRITE | PROT_READ = práva k paměti
    // MAP_SHARED = změny budou viditelné pro ostatní procesy (opakem je MAP_PRIVATE)
    ptr = mmap(0, velikost, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
#endif

    // -------------------------------------------------------------------------
    // SPOLEČNÁ ČÁST - Práce s daty
    // -------------------------------------------------------------------------
    
    std::cout << "[Writer] Pamet pripravena. Adresa v mem procesu: " << ptr << std::endl;
    std::cout << "[Writer] Zapisuji data..." << std::endl;

    // Zápis dat do sdílené paměti je stejný jako zápis do jakéhokoliv pole.
    // Používáme memcpy pro kopírování bytů.
    // +1 pro kopírování ukončovacího znaku '\0'
    memcpy(ptr, zprava, strlen(zprava) + 1);

    std::cout << "[Writer] Hotovo. Cekam na ukonceni..." << std::endl;
    std::cout << " (NEZAVIREJTE tento program, dokud si data neprecte Reader)" << std::endl;
    std::cout << " [Stisknete ENTER pro ukonceni]" << std::endl;
    std::cin.get();

    // -------------------------------------------------------------------------
    // Úklid (Cleanup)
    // -------------------------------------------------------------------------
#ifdef _WIN32
    UnmapViewOfFile(ptr);  // Zruší mapování ukazatele
    CloseHandle(hMapFile); // Zavře handle. Pokud byl poslední, paměť se uvolní.
#else
    munmap(ptr, velikost); // Zruší mapování
    close(shm_fd);         // Zavře file descriptor
    shm_unlink(nazev);     // DŮLEŽITÉ: Smaže objekt z /dev/shm. 
                           // Bez tohoto by paměť v systému zůstala i po vypnutí programu.
#endif

    std::cout << "[Writer] Pamet uvolnena. Konec." << std::endl;
    return 0;
}