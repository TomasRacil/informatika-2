# **18 - Sdílená paměť (Shared Memory)**

Stejně jako v C++, i v Pythonu můžeme využít nejrychlejší způsob komunikace mezi procesy: **Sdílenou paměť**.

Zatímco klasický `multiprocessing.Queue` data serializuje  a posílá pomocí pipe, sdílená paměť umožňuje dvěma procesům dívat se na stejný kus RAM.

Od Pythonu 3.8 máme k dispozici modul **`multiprocessing.shared_memory`**, který práci výrazně zjednodušuje.

## **1. Princip `SharedMemory`**

Funguje to velmi podobně jako v C++:

1. **Vytvoření:** Jeden proces (Writer) požádá OS o blok paměti a dá mu jméno.  
2. **Připojení:** Jiný proces (Reader) se připojí pomocí tohoto jména.  
3. **Buffer Protocol:** Python nám paměť zpřístupní jako pole bytů (`memoryview`). Můžeme do něj zapisovat jako do pole.

## **2. Klíčové metody**
```python
from multiprocessing.shared_memory import SharedMemory

# Vytvoření (Writer)  
shm = SharedMemory(name="MojePamet", create=True, size=1024)

# Připojení (Reader)  
shm = SharedMemory(name="MojePamet")

# Práce s daty (jako s polem bytů)  
shm.buf[0] = 65  # Zápis 'A' na první pozici

# Úklid (Velmi důležité!)  
shm.close()  # Zavře handle v tomto procesu  
shm.unlink() # Smaže paměť z OS (volá pouze ten, kdo ji vytvořil!)
```
## **3. Rizika (Memory Leaks)**

V Pythonu jsme zvyklí, že Garbage Collector uklízí za nás. U sdílené paměti to neplatí!  
Pokud proces spadne dříve, než zavolá `unlink()`, sdílená paměť v operačním systému zůstane "viset" a zabírá místo, dokud nerestartujete počítač (nebo ji nesmažete ručně).  
**Tip:** Vždy používejte `try...finally` bloky pro zajištění úklidu.
---
## **Cvičení**

### **1. Zapisovatel (Writer)**
Napište skript, který:
1. Vytvoří sdílenou paměť o velikosti 5 bajtů se jménem "TestShared".
2. Na první pozici (`buf[0]`) zapíše číslo 100.
3. Čeká na stisk Enteru (aby se program hned neukončil) a nakonec zavolá `unlink()`.

### **2. Čtenář (Reader)**
Napište druhý skript (spusťte v jiném terminálu), který:
1. Připojí se k "TestShared".
2. Přečte hodnotu z první pozice.
3. Vypíše ji.
