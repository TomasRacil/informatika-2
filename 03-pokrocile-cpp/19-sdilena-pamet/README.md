# **19 - Sdílená paměť (Shared Memory)**

## **1. Teoretický úvod: Jak funguje paměť procesu?**

Abychom pochopili sdílenou paměť, musíme si připomenout, jak funguje paměť v moderních operačních systémech.

### **Izolace procesů (Virtuální paměť)**

Každý program (proces), který spustíte, si myslí, že má celou paměť RAM jen pro sebe. Operační systém mu přidělí **Virtuální adresní prostor** (např. od `0x0000` do `0xFFFF`).

* Když Proces A zapíše na adresu `0x1234`, OS to fyzicky uloží do RAM na adresu `A_100`.  
* Když Proces B zapíše na adresu `0x1234`, OS to fyzicky uloží do RAM na adresu `B_500`.

Procesy na sebe **nevidí**. Nemohou si navzájem přepsat data (což je dobře z hlediska bezpečnosti a stability).

### **Princip Sdílené paměti**

Sdílená paměť je "díra" v této izolaci. Požádáme operační systém, aby vzal kus fyzické RAM a **namapoval ho do virtuálního prostoru obou procesů současně**.

* Proces A vidí sdílený kus na své adrese `0x5000`.  
* Proces B vidí ten **stejný** kus fyzické paměti na své adrese `0x8000`.  
* Pokud A zapíše data, B je vidí **okamžitě** (rychlostí přístupu do RAM). Nedochází k žádnému kopírování dat (Zero-Copy), jako je tomu u Socketů nebo Pipes.

## **2. Implementace v C++**

Protože C++ standard (zatím) nemá knihovnu pro sdílenou paměť, musíme použít služby operačního systému. Ty se bohužel liší.

### **Windows (File Mapping)**

Windows používá koncept "Mapování souborů". Sdílená paměť je pro něj jen speciální případ souboru, který neleží na disku, ale v `pagefile` (stránkovacím souboru).

* `CreateFileMapping`: Vytvoří objekt paměti.  
* `MapViewOfFile`: Zpřístupní tento objekt jako ukazatel (`void*`) v našem programu.

### **Linux / POSIX (Shared Memory Objects)**

Linux používá standard POSIX. Sdílené paměti vypadají jako soubory ve složce `/dev/shm/`.

* `shm_open`: Vytvoří objekt (jako `open` pro soubor).  
* `ftruncate`: Nastaví velikost (jako u souboru).  
* `mmap`: Namapuje objekt do adresního prostoru procesu.

## **3. Rizika a Synchronizace (Race Condition)**

Sdílená paměť je nejrychlejší IPC (Inter-Process Communication), ale také nejnebezpečnější. Operační systém pouze nasdílí paměť, ale **neřeší, kdo do ní kdy zapisuje**.

### **Problém: Race Condition (Souběh)**

Představte si, že Proces A a Proces B chtějí současně zvýšit sdílené počítadlo (`counter++`).

1. **Proces A** načte hodnotu `10`.  
2. **Proces B** načte hodnotu `10` (protože A ji ještě nestihl změnit).  
3. **Proces A** zvýší na `11` a zapíše.  
4. Proces B zvýší na `11` a zapíše.  
   Výsledek: Hodnota je `11`, ale měla být `12`. Jedna operace se "ztratila".

### **Řešení: Meziprocesová synchronizace**

Běžný `std::mutex` zde nefunguje, protože ten je lokální pro jeden proces. Musíme použít synchronizační objekt operačního systému, který má jméno (aby ho našel i druhý proces).

Pojmenovaný Semafor (Named Semaphore):  
Funguje jako zámek, který leží v systému (mimo paměť našich procesů).

* **Windows:** `CreateSemaphore` (s názvem) / `WaitForSingleObject` (Lock) / `ReleaseSemaphore` (Unlock).  
* **Linux:** `sem_open` (s názvem) / `sem_wait` (Lock) / `sem_post` (Unlock).

**Příklady v této sekci:**

1. [01-zaklady](./01-zaklady): Jednoduchý přenos textu (Writer/Reader).  
2. [02-race-condition](./02-race-condition): Ukázka chyby při souběžném zápisu.  
3. [03-synchronizace](./03-synchronizace): Oprava chyby pomocí pojmenovaného semaforu.
---
## **Cvičení**

### **1. Časovač (Writer & Reader)**
Napište dva programy:
1. **writer.cpp**: Vytvoří sdílenou paměť (o velikosti `sizeof(long)`). V nekonečném cyklu do ní každou sekundu zapisuje aktuální čas (Unix timestamp).
2. **reader.cpp**: Připojí se ke stejné sdílené paměti a v cyklu vypisuje hodnotu, kterou tam writer zapsal.
Ověřte, že se hodnota v readeru mění, i když writer běží v jiném terminálu.

### **2. Implementace semaforu**
Upravte oba programy tak, aby používaly **pojmenovaný semafor** (`sem_open`).
- Writer: Zamkne semafor -> zapíše -> odemkne.
- Reader: Zamkne semafor -> přečte -> odemkne.
Tím zajistíte, že reader nebude čist nekompletní data (i když u jednoho `long` to není tak kritické, jde o princip).
