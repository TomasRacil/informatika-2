# **21 - Asynchronní programování v C++**

V předchozích částech o vláknech (**sekce 18**) jsme se naučili, jak spouštět kód paralelně. Práce přímo s vlákny je ale nízkoúrovňová a často zbytečně složitá. V této sekci se podíváme na moderní asynchronní přístupy, které C++ nabízí.

## **1. Problém s vláknem (`std::thread`)**

Při použití `std::thread` narážíme na několik omezení:
1. **Návratová hodnota:** Vlákno samo o sobě neumí vrátit výsledek (musíme použít sdílenou proměnnou nebo referenci).
2. **Výjimky:** Pokud ve vlákně nastane výjimka a není tam zachycena, celý program spadne (`std::terminate`).
3. **Režie:** Každé nové vlákno stojí OS paměť (stack) a čas na vytvoření.

## **2. Úlohy a přísliby: `std::future` a `std::promise`**

Tato dvojice tvoří nízkoúrovňový komunikační kanál mezi dvěma vlákny. Jeden konec (producer) zapisuje a druhý (consumer) čte.

- **`std::promise` (Zapisovač):** Slouží k nastavení hodnoty (výsledku). Každý `std::promise` je propojen s jedním objektem `std::future`.
- **`std::future` (Čtečka):** Slouží k odběru výsledku. Pokud výsledek ještě není hotov, volání `.get()` zablokuje vlákno, dokud se hodnota neobjeví.

### **Vztah 1:1 a Shared State**
Když vytvoříte `std::promise`, vytvoří se **sdílený stav** (shared state). Z něj si pak pomocí `promise.get_future()` vytáhnete "čtečku". 

**Důležitá pravidla:**
1.  **Jednorázovost:** Metodu `.get()` na objektu `std::future` můžete zavolat **pouze jednou**. Poté se sdílený stav stane neplatným.
2.  **Synchronizace:** Nemusíte používat mutexy k ochraně předávané hodnoty – Standardní knihovna zaručuje, že předání z `promise` do `future` je vláknově bezpečné.

```cpp
#include <future>
#include <thread>

std::promise<int> pr;
std::future<int> fut = pr.get_future();

// Vlákno A (vypočítá hodnotu)
pr.set_value(42); 

// Vlákno B (přečte hodnotu)
int vysledek = fut.get(); // Zde se čeká
```

## **3. Vyšší abstrakce: `std::async`**

`std::async` je funkce, která slouží ke spuštění úlohy asynchronně. Na rozdíl od `std::thread` nám umožňuje definovat **jak** a **kdy** se má kód spustit pomocí tzv. *launch policy*.

### **Vztah k procesoru a OS:**
Když zavoláte `std::async`, nežádáte přímo procesor o čas, ale žádáte **Standardní knihovnu C++** a **Operační systém**, aby naplánovali úlohu. 

Máme dvě hlavní strategie spuštění:

1.  **`std::launch::async` (Vynucené vlákno):**
    *   **Vztah k OS:** Knihovna požádá OS o vytvoření nového **vlákna** (v rámci vašeho procesu).
    *   **Vztah k CPU:** Plánovač OS (Scheduler) se pokusí toto vlákno umístit na **volné jádro procesoru**. Pokud máte více jader, úloha běží fyzicky paralelně s hlavním vláknem.
    *   **Výhoda:** Skutečný paralelismus.

2.  **`std::launch::deferred` (Odložené vykonání):**
    *   **Princip:** Úloha se nespustí hned a nevytvoří nové vlákno. Kód se vykoná až v okamžiku, kdy poprvé zavoláte `.get()` nebo `.wait()`.
    *   **Vztah k CPU:** Úloha běží **ve stejném vlákně** (a tedy na stejném jádře) jako volající kód. Jde o tzv. *lazy evaluation*.
    *   **Výhoda:** Šetří zdroje, pokud výsledek nakonec nebudete potřebovat.

### **Jak `std::async` funguje uvnitř?**

Když použijete `std::async`, vytvoří se tzv. **Shared State** (sdílený stav) v paměti (heap). Tento stav slouží jako komunikační kanál mezi asynchronním úkolem a vaším hlavním kódem.

1.  **Předávání výsledků:** Úkol zapíše výsledek do sdíleného stavu. `std::future` si jej odtud přečte.
2.  **Předávání výjimek:** Pokud v úkolu vyletí výjimka, nezabije program hned. Místo toho se "zachytí" do sdíleného stavu. Vyhodí se (re-throw) až v okamžiku, kdy zavoláte `future.get()`. To je obrovská výhoda oproti `std::thread`.

### **Proč nepoužívat jen vlákna?**
Proces má v OS omezený počet vláken a každé vlákno má svou režii (alokace zásobníku cca 1MB). `std::async` dává implementaci (překladači) svobodu: pokud je systém přetížen, může se rozhodnout nové vlákno nevytvářet a úlohu spustit jinak (např. v rámci vnitřního fondu vláken – *Thread Pool*), což je k systému šetrnější než nekontrolované vytváření stovek `std::thread`.

```cpp
// Příklad: Vynucení paralelního běhu na jiném jádře
auto future = std::async(std::launch::async, moje_funkce);
```

## **4. C++20 Korutiny (Coroutines)**

Největší novinkou v C++20 jsou korutiny. Na rozdíl od běžné funkce se korutina může **pozastavit** (suspend) a později **obnovit** (resume).

### **Jak korutina funguje?**

Na rozdíl od Pythonu nebo JavaScriptu, kde má jazyk vestavěný "Event Loop", v C++ je korutina čistě **přepis kódu překladačem**.

1.  **Stavový automat (State Machine):** Překladač vezme vaši funkci a rozseká ji na části v místech, kde je `co_await`. Vytvoří skrytý objekt (tzv. *Coroutine Frame*), který si pamatuje, kde se v kódu skončilo a jaké byly hodnoty proměnných.
2.  **Stackless (Bez vlastního zásobníku):** Běžná funkce potřebuje "Stack Frame" v paměti po celou dobu běhu. Korutina se při pozastavení ze zásobníku "odpaří" a zůstává jen malý objekt na haldě (heap). To umožňuje mít miliony běžících korutin najednou, což by s vlákny nebylo možné.
3.  **Absence Event Loopu:** C++ vám dává nástroje (`co_await` atd.), ale neříká, *kdy* se má korutina probudit. To musí zajistit programátor nebo knihovna (např. po dokončení síťového požadavku).

### **Nová klíčová slova:**
- **`co_await`**: "Tady se zastav a počkej, až mě někdo probudí s výsledkem."
- **`co_return`**: "Tady končím a toto je můj finální výsledek."
- **`co_yield`**: "Tady máš hodnotu, zastav mě, ale až mě probudíš, pokračuj hned za tímto řádkem." (Využívá se pro tvorbu nekonečných řad dat - generátorů).

> [!IMPORTANT]
> Pro použití korutin potřebujete návratový typ, který splňuje tzv. *Coroutine Promise* rozhraní. C++20 neobsahuje standardní typ (jako `std::task`), takže v praxi se často používají knihovny jako **cppcoro** nebo **Boost.Asio**.

## **5. Shrnutí: Kdy co použít?**

| Nástroj | Kdy použít? | Výhoda |
| :--- | :--- | :--- |
| **`std::thread`** | Nízkoúrovňové řízení, dlouho běžící vlákna. | Plná kontrola. |
| **`std::async`** | Jednorázové výpočty na pozadí. | Snadné předání výsledku a výjimek. |
| **`co_await`** | I/O operace, tisíce souběžných úkolů. | Minimální režie (lehčí než vlákna). |

---
## **Cvičení**

### **1. Async výpočet**
Použijte `std::async` k výpočtu faktoriálu čísla 10 na pozadí.
Mezitím v hlavním vlákně vypisujte tečky ("..."), dokud výpočet neskončí (použijte `wait_for` s nulovým časem nebo jen prostě zavolejte `.get()` na konci).

### **2. Promise / Future**
Vytvořte vlákno, které bude čekat na signál (pomocí `std::future<void>`), aby začalo pracovat. Hlavní vlákno pošle signál pomocí `std::promise<void>` po stisku klávesy Enter.
