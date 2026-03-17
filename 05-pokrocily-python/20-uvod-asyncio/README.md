# **20 - Úvod do AsyncIO**

V tomto modulu se naučíme, jak v Pythonu psát asynchronní kód. Tento přístup umožňuje programu dělat více věcí "najednou" bez nutnosti spravovat složitá vlákna nebo procesy.

## **1. Koncept: Proč AsyncIO?**

Už známe:
- **Vlákna (Threading - sekce 16):** Dobrá pro I/O, ale limitovaná GILem a paměťově náročná při tisících vláknech.
- **Procesy (Multiprocessing - sekce 17):** Skutečný paralelismus pro výpočty, ale drahý start a složitá komunikace.

**AsyncIO** je třetí cesta: **Konkurence v jednom vlákně.** Pomocí tzv. **Event Loopu** (smyčky událostí) aplikace efektivně přepíná mezi úkoly přesně v momentě, kdy jeden z nich na něco čeká (např. na síť nebo disk).

## **2. Výhody AsyncIO**
- **Extrémní škálovatelnost:** Jedno vlákno zvládne obsloužit tisíce spojení s minimální pamětí.
- **Žádné Race Conditions (skoro):** Protože kód běží vždy v jednom vlákně, nemusíme (většinou) řešit zamykání proměnných pomocí `Lock`.
- **Explicitní přepínání:** Programátor přesně určuje, kde se může kód pozastavit (pomocí `await`).

## **3. Základní klíčová slova**

1.  **`async def`**: Definuje **coroutinu** (speciální funkci, kterou lze pozastavit).
2.  **`await`**: Pozastaví běh coroutiny a předá řízení Event Loopu. Během tohoto čekání může loop provádět jinou práci.
3.  **`asyncio.run()`**: Vstupní bod pro spuštění asynchronního programu.

### **Příklad: Blokující vs. Asynchronní spánek**

```python
import asyncio
import time

# BLOKUJÍCÍ (vše se zastaví, jak známe ze sekce 16)
time.sleep(1) 

# NEBLOKUJÍCÍ (vlákno se uvolní pro jiné úkoly)
await asyncio.sleep(1) 
```

## **4. Souběžný běh (`asyncio.gather`)**

Pokud máme 10 úkolů a každý trvá 1 sekundu:
- S `time.sleep` v cyklu to trvá **10 sekund**.
- S `asyncio.sleep` a `asyncio.gather` to trvá **1 sekundu**.

```python
async def uloh(jmeno):
    print(f"Start {jmeno}")
    await asyncio.sleep(1)
    print(f"Konec {jmeno}")

async def main():
    # Spustí vše najednou v rámci jedné smyčky!
    await asyncio.gather(uloh("A"), uloh("B"), uloh("C"))
```

---
## **Cvičení**

### **1. Snídaně**
Napište dvě asynchronní funkce:
- `uvar_kavu()` (trvá 2 sekundy).
- `opeci_toust()` (trvá 1 sekundu).
Spusťte je **souběžně** pomocí `asyncio.gather` a změřte celkový čas (měl by být cca 2 sekundy).

### **2. Sekvence vs. Paralelismus**
Zkuste ty samé funkce spustit pomocí `await` za sebou (uvnitř `main`).
- `await uvar_kavu()`
- `await opeci_toust()`
Změřte čas (měl by být 3 sekundy).
