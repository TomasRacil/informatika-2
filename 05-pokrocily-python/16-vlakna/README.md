# **16 - Vlákna (Threading) v Pythonu**

V předchozích lekcích C++ jsme viděli, jak vlákna umožňují provádět více operací současně a využívat více jader procesoru. V Pythonu je situace trochu jiná a (pro C++ programátory) často překvapivá.

## **1. Hlavní rozdíl: GIL (Global Interpreter Lock)**

Standardní interpret Pythonu (CPython) obsahuje mechanismus zvaný **GIL**. Je to zámek, který zajišťuje, že **v jeden okamžik může běžet pouze jedno vlákno Python kódu**.

### **Co to znamená v praxi?**

* **V C++:** Pokud máte 4 jádra a spustíte 4 vlákna s těžkým výpočtem, úloha bude hotová 4x rychleji (skutečný paralelismus).  
* **V Pythonu:** Pokud spustíte 4 vlákna s těžkým výpočtem, budou se na jednom jádře střídat. Kvůli režii přepínání to bude pravděpodobně **pomalejší** než bez vláken.

### **Proč tedy vlákna v Pythonu používat?**

Vlákna v Pythonu jsou skvělá pro úlohy typu **I/O Bound** (čekání na vstup/výstup), nikoliv **CPU Bound** (výpočty).

| Typ úlohy | Příklad | Pomohou vlákna? |
| :---- | :---- | :---- |
| **I/O Bound** | Stahování souborů, dotazy do databáze, čekání na uživatele, čtení disku. | **ANO!** (Zatímco jedno vlákno čeká na data, GIL se uvolní a jiné může pracovat). |
| **CPU Bound** | Šifrování, zpracování obrazu, trénování AI, násobení matic. | **NE!** (Vlákna se perou o CPU). |

Jak řešit náročné výpočty?  
Pokud potřebujete využít více jader pro výpočty, musíte v Pythonu použít Multiprocessing (více procesů místo více vláken). Tím se budeme zabývat v příštích lekcích.

## **2. Modul `threading`**

Pro práci s vlákny používáme modul `threading`.

```python
import threading

def pracuj():  
    print("Vlákno běží")

t = threading.Thread(target=pracuj)  
t.start() # Spustí vlákno  
t.join()  # Počká na dokončení
```

## **3. Synchronizace (Race Condition)**

I když máme GIL, k Race Condition (chybě souběhu) může dojít!  
GIL sice zaručuje atomicitu jedné instrukce bajtkódu, ale operace jako `x += 1` se skládají z více instrukcí (načíst, přičíst, uložit). Pokud se vlákna přepnou uprostřed, data se poškodí.  
Proto i v Pythonu musíme používat:

* `threading.Lock` (zámek)  
* `threading.Semaphore`  
* `threading.Event`

## **4. Bezpečná komunikace: `queue.Queue`**

Zatímco v C++ jsme museli `std::vector` chránit mutexem, Python nabízí `queue.Queue`, která je **Thread-Safe**. Můžete do ní bezpečně vkládat data z více vláken bez zamykání.
---
## **Cvičení**

### **1. Paralelní čekání**
Importujte `time` a `threading`.
1. Vytvořte funkci `cekej(sekund)`, která jen spí (`time.sleep`).
2. Spusťte dvě vlákna, každé čeká 2 sekundy.
3. Změřte celkový čas běhu programu. Měl by být cca 2 sekundy, nikoliv 4. Proč?

### **2. Zamykání**
Mějte globální proměnnou `bankovni_ucet = 0`.
Spusťte 100 vláken, každé přičte 1. Použijte `threading.Lock`, abyste zajistili, že výsledek bude vždy přesně 100 (bez zámku by mohl být menší kvůli Race Condition).
