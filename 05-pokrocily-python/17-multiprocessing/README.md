# **17 - Multiprocessing**

V minulé lekci jsme zjistili, že vlákna (threading) jsou v Pythonu limitována zámkem GIL a hodí se hlavně na I/O operace. Pokud chceme využít výkon více jader CPU pro výpočty, musíme použít **Procesy**.

## **1. Teoretický úvod: Co je to Proces?**

Než se pustíme do Pythonu, musíme pochopit, jak funguje proces v operačním systému.

### **Definice**

Proces je **běžící instance programu**. Když spustíte `python main.py`, operační systém vytvoří nový proces.

### **Klíčové vlastnosti procesu:**

1. **Izolovaná paměť:** Každý proces má svůj **vlastní adresní prostor** (RAM).  
   * Pokud Proces A změní proměnnou `x = 5`, Proces B to **nevidí**. Má své vlastní `x`.  
   * Tato izolace zajišťuje bezpečnost (jeden program neshodí druhý), ale ztěžuje výměnu dat.  
2. **Vlastní zdroje:** Proces vlastní otevřené soubory, síťová spojení a další systémové prostředky.  
3. **PID (Process ID):** Každý proces má unikátní číslo, kterým ho identifikuje OS.  
4. **Heavyweight:** Vytvoření nového procesu (zejména v Pythonu) trvá déle a stojí více paměti než vytvoření vlákna, protože se musí zkopírovat/vytvořit celé prostředí interpretu.

## **2. Python a Multiprocessing: Obcházení GIL**

Modul `multiprocessing` v Pythonu vytváří nové pod-procesy.
Každý takový pod-proces je zcela nová instance Python interpretu.

* Každý proces má svůj vlastní GIL.  
* Každý proces běží na jiném jádře CPU.  
* **Výsledek:** Skutečný paralelismus, kde GIL nevadí (protože každý proces má svůj vlastní).

## **2. Srovnání: Threading vs. Multiprocessing**

| Vlastnost | Threading (Vlákna) | Multiprocessing (Procesy) |
| :---- | :---- | :---- |
| **Sdílení paměti** | **ANO** (Všechna vlákna vidí stejné proměnné). | **NE** (Každý proces má vlastní kopii paměti). |
| **Režie (Overhead)** | Nízká (Rychlý start). | Vysoká (Musí se nastartovat celý Python). |
| **Využití CPU** | Max 1 jádro (kvůli GIL). | Všechna dostupná jádra. |
| **Vhodné pro** | I/O operace (stahování, disk). | CPU operace (matematika, AI, šifrování). |

## **4. Důležitá pravidla pro Windows**

Na operačním systému Windows (a macOS od Python 3.8) startují nové procesy trochu jinak než na Linuxu (nepoužívá se `fork`, ale `spawn`).  
To znamená, že nový proces importuje váš skript znovu od začátku.  
**Pravidlo:** Na Windows (a macOS) musí být kód spouštějící procesy chráněn podmínkou `if __name__ == "__main__":`.

```python
if __name__ == "__main__":  
    # Zde startujte procesy
    p = multiprocessing.Process(...)
    p.start()
```

Pokud to neuděláte, nový proces při startu znovu načte skript, znovu narazí na příkaz k vytvoření procesu a zacyklí se ("rekurzivní" vytváření procesů, které shodí systém nebo vyhodí chybu).

## **4. Komunikace (IPC)**

Protože procesy nesdílejí paměť, nemůžete jednoduše zapsat do globální proměnné a čekat, že to druhý proces uvidí. Data se musí posílat.

* **Queue**: Fronta zpráv. Jeden proces data vloží, data se serializují (zabalí), pošlou přes paměť OS a druhý proces si je vyzvedne a deserializuje.
* **Pipe**: Přímé spojení mezi dvěma procesy.  
* **Value, Array**: Sdílená paměť (Shared Memory), která obchází izolaci (viz další lekce).

Při posílání dat mezi procesy dochází k tzv. **Picklingu** (serializaci), což může být pomalé u velkých objemů dat.
---
## **Cvičení**

### **1. CPU makačka**
Vytvořte funkci `narocna_prace()`, která sečte čísla od 1 do 10 milionů.
Spusťte tuto funkci 4x **paralelně** pomocí `multiprocessing.Process`.
Sledujte vytížení procesoru (např. ve správci úloh/htop), zda se využila všechna jádra.

### **2. Posílání výsledků**
Upravte funkci tak, aby výsledek vložila do `multiprocessing.Queue`.
V hlavním procesu () vytáhněte výsledky z fronty a sečtěte je.
