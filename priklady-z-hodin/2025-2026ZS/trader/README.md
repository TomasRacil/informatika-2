# Zadání: "Wall Street Simulator" (Thread Safety & Deadlocks)

**Cíl:** Naprogramovat jádro burzovního systému. Musíte zajistit, aby se v miliardách transakcí neztratil ani cent a aby se systém nezastavil v křeči (deadlock).

**Klíčové prvky:**

1. **Zachování hmoty:** Peníze a akcie nemohou vznikat ani zanikat. Co jeden utratí, druhý musí dostat.
2. **Dynamický trh:** Ceny akcií se mění s každým obchodem.
3. **Vlákna:** Každý obchodník je samostatné vlákno.

---

> [!NOTE]
> **Realita vs. Simulace:** V reálném světě retailoví investoři obchodují téměř výhradně přes **brokery** (zprostředkovatele) na burzách (jako NYSE nebo BCPP). Přímé obchody mezi lidmi (**P2P**) jsou vzácné a probíhá tak spíše mimoburzovní trh (OTC) u velkých institucí nebo u kryptoměn. V tomto zadání simulujeme oba světy.

---

### Fáze 1: Divoký západ (Race Condition)

Naprogramujte systém bez jakékoliv synchronizace.

* **Třída `Market` (Centrální burza):**
* Drží zásobu akcií (např. 10 000 ks od AAPL).
* Drží aktuální ceny (např. AAPL = 150 $).
* **Mechanismus ceny:** Cena není náhodná, ale reaguje na obchodování. Nákup zvyšuje poptávku (cenu), prodej zvyšuje nabídku (cenu snižuje).

* **Třída `Trader` (Investoři):**
* Každý má startovní kapitál (např. 1 000 $).
* Každý má prázdné portfolio.
* V nekonečné smyčce náhodně **kupuje** nebo **prodává** akcie přes `Market`.

* **Logika nákupu:**
1. Trader zjistí cenu.
2. Pokud má dost peněz:
* Odečte peníze sobě, přičte je Marketu (poplatek/zisk burzy).
* Market odečte akcii, Trader si ji přičte.

* **Očekávaný problém:**
* Spusťte 10-50 vláken.
* Na konci sečtěte všechny peníze v systému (Market + Traders) a všechny akcie.
* **Výsledek:** Peníze nebudou sedět (někdo zaplatil, ale Market peníze nepřipsal, protože jiné vlákno přepsalo paměť).
* **Výzva:** Dokážete v kódu najít přesný řádek, kde k této chybě dochází? Co se stane, když se dvě vlákna pokusí změnit `market_cash` ve stejný okamžik?

### Fáze 2: Regulovaný trh (Mutex)

Opravte Fázi 1 zavedením `std::mutex` do třídy `Market`.

* Zajistěte, aby celá transakce (Změna ceny + Převod peněz + Převod akcie) byla **atomická**.
* Nesmí se stát, že se změní cena, ale akcie se nepřevede.
* **Výsledek:** Audit na konci musí sedět na dolar přesně.

### Fáze 3: OTC Obchody (Deadlock)

Burza zavádí novou funkci: **Přímý obchod mezi tradery** (Peer-to-Peer).

* Implementujte funkci `trade_direct(Trader A, Trader B)`.
* Trader A chce koupit akcie přímo od Tradera B (obchází Market).
* **Synchronizace:**
* Musíte zamknout Tradera A (aby mu někdo jiný nesebral peníze během transakce).
* Musíte zamknout Tradera B (aby mu někdo jiný nesebral akcie).

* **Simulace Deadlocku:**
* Vlákno 1: Trader 0 kupuje od Tradera 1.
* Vlákno 2: Trader 1 kupuje od Tradera 0.
* Pokud zamknete `A` a čekáte na `B`, zatímco on drží `B` a čeká na `A`, systém zamrzne.


* **Úkol:** Vyřešte deadlock. Prozkoumejte strategie pro bezpečné zamykání více zdrojů najednou a podívejte se na moderní C++ nástroje, které zaručují atomické zamknutí více mutexů bez rizika uváznutí.

### Fáze 4: Dashboard (Vizualizace)

Burza potřebuje moderní dohled. Vaším úkolem je přidat do systému "Monitorovací vlákno".

* **Požadavky:**
    * Vytvořte samostatné vlákno, které bude periodicky (např. každých 100 ms) vypisovat stav trhu.
    * **Živý graf:** Zobrazujte vývoj ceny (stačí jednoduchý ASCII graf v konzoli nebo textový výpis trendu).
    * **Historie obchodů:** Zobrazujte posledních 5-10 provedených transakcí.
    * **Synchronizace:** Toto je nejtěžší část. Musíte vymyslet, jak bezpečně předávat data o obchodech z obchodních vláken do monitorovacího vlákna, aniž byste výrazně zpomalili trh nebo způsobili Race Condition v historii.
    * **Mechanismus sběru dat si navrhněte sami.** Boilerplate záměrně neobsahuje žádné struktury pro ukládání historie.
---

### Bonus: Inteligentní obchodování a Portfolio

Pokud máte vše hotové, zkuste systém posunout na další úroveň:

*   **Více akcií:** Přidejte do burzy další symboly (např. `TSLA`, `BTC`, `GOOGL`).
*   **Strategie:** Místo náhodného klikání naprogramujte traderům jednoduchou logiku "Kupuj levně, prodávej draze" (např. nákup při poklesu o 5 %, prodej při zisku 10 %).
*   **Audit zisku:** Na konci vypište pro každého obchodníka:
    *   **Realizovaný zisk:** Kolik peněz (cash) vydělal/prodělal oproti začátku.
    *   **Nerealizovaný zisk:** Hodnota akcií, které stále drží (při aktuální tržní ceně).
*   **Rizikové profily:** Rozlište tradery podle jejich ochoty riskovat (přidejte jim jména jako "Konzervativní", "Agresivní" atd.):
    *   Každý profil má jiné parametry pro náklad a prodej (např. agresivní trader nakupuje už při malém poklesu a prodává až při velkém zisku).
    *   Vypište název strategie v reportu.
*   **Interaktivní ovládání:** Přidejte možnost simulaci ovládat za běhu:
    *   Klávesa `p`: Pozastaví/opět spustí simulaci a vypíše aktuální stav zisku všech traderů.
    *   **Celkový progres:** Seřaďte tabulku sestupně podle celkového zisku (Realizovaný + Nerealizovaný), aby byl vítěz vždy na prvním místě.
*   **Decentralizovaná burza (Order Book):** Pokud je centrální burza obsazená (`try_lock`), implementujte systém párování nabídek:
    *   **Prodejci:** Místo čekání na burzu zapíší svoji nabídku (id, symbol) do sdílené fronty.
    *   **Kupující:** Pokud je burza obsazená, nejdříve prohledají tuto frontu a pokud najdou odpovídající akcii, provedou P2P obchod.
    *   **Market Clearing:** Samotná burza může ve volných chvílích tyto inzeráty z knihy "vysávat" a odkupovat akcie přímo od čekajících prodejců, pokud má dostatek hotovosti.

### Soubory v projektu
*   **[boilerplate.cpp](boilerplate.cpp)**: Startovní kód. Obsahuje základní struktury a logiku, ale postrádá synchronizaci a správu vláken. Zde budete pracovat.
*   **[solution.cpp](solution.cpp)**: Kompletní řešení se všemi fázemi i bonusy (včetně interaktivního ovládání a grafů). Slouží pro inspiraci nebo kontrolu.

### Jak začít
1. Prozkoumejte soubor `boilerplate.cpp`.
2. Zkuste ho zkompilovat a spustit – uvidíte, že audit na konci nesedí (Race Condition).
3. Postupujte podle fází 1 až 4.

```bash
# Zkopírujte boilerplate pro vaši práci
cp boilerplate.cpp my_trader.cpp

# Kompilace (vždy s -lpthread)
g++ -std=c++17 my_trader.cpp -o trader -lpthread

# Spuštění
./trader
```