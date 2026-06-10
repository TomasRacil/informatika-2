# Kritéria hodnocení studentských projektů (C++ – 2. semestr)

---

## Přehled bodových kategorií (Max. 100 bodů + Bonusy)

| Kategorie | Popis zaměření | Max. body |
| :--- | :--- | :---: |
| **1. Dokumentace a instalace** | README, návod k sestavení a spuštění, popis funkčnosti, forma a přehlednost | **10** |
| **2. Funkčnost a logika** | Splnění zadání, správné chování, stabilita, ošetření chyb (plný počet = production ready) | **20** |
| **3. Architektura a čistota C++** | Rozdělení do souborů, správa paměti, OOP (plný počet = production ready) | **20** |
| **4. Inovace a technologie** | Použití externích knihoven, zajímavé/inovativní použití standardních prvků | **15** |
| **5. Rozsah a úsilí** | Celková náročnost, hustota logiky, kvalita před kvantitou | **15** |
| **6. Prezentace a obhajoba** | Schopnost vysvětlit kód a obhájit řešení | **20** |
| **Bonusová kategorie** | Prostor pro vyučujícího k ocenění mimořádně povedené práce a unikátních prvků | **+10** |

---

## Podrobná kritéria hodnocení

### 1. Dokumentace a instalace (max. 10 bodů)
Hodnotí se jak **obsah**, tak **forma a přehlednost** dokumentace (typicky v souboru `README.md`). Projekt by měl být snadno přenositelný, sestavitelný a přehledně strukturovaný.
* **10 bodů**: Dokumentace je kompletní, logicky strukturovaná (s využitím prvků markdownu jako nadpisy, seznamy, kódové bloky) a vysoce přehledná. Obsahuje jasný návod k sestavení (např. pomocí `CMakeLists.txt`, `Makefile` nebo VS Solution), seznam závislostí a popis ovládání.
* **7–9 bodů**: Informace jsou sice kompletní, ale dokumentace má horší formu (např. chybí strukturování, je nepřehledná, špatně formátovaná) nebo obsahuje drobné mezery v návodu.
* **4–6 bodů**: Návod je neúplný, sestavení vyžaduje dodatečné úsilí a dohledávání informací. Forma dokumentace je velmi slabá a nepřehledná.
* **1–3 body**: Zásadní nedostatky v obsahu i formě. Chybí návod k sestavení, spuštění je možné jen s velkým úsilím.
* **0 bodů**: Dokumentace zcela chybí.

> Pokud projekt nelze vůbec sestavit kvůli chybějícímu popisu závislostí nebo naprosto chybějícímu postupu kompilace, strhává se v této kategorii až 6 bodů. Nefunkčnost sestavení z důvodu chybějící knihovny se však nepenalizuje v logice/funkčnosti (princip *No Double Jeopardy*).

---

### 2. Funkčnost a logika programu (max. 20 bodů)
Hodnotí se stabilita aplikace, to, jak dobře plní svůj účel, a míra splnění dohodnutého zadání (specifikace projektu).
* **20 bodů (Production Ready)**: Plný počet bodů je vyhrazen pouze pro projekty, které jsou na úrovni připravené pro produkční nasazení (production-ready) nebo se této úrovni velmi těsně blíží. Aplikace plně realizuje dohodnuté zadání, funguje naprosto bezchybně, stabilně, bez neošetřených pádů, korektně validuje všechny uživatelské vstupy a bezpečně ošetřuje hraniční i chybové stavy.
* **15–19 bodů**: Aplikace splňuje standardní nároky na studentský projekt a plní dohodnuté zadání. Většinou funguje bez problémů, ale vykazuje drobné mezery v ošetření nestandardních vstupů nebo má drobné funkční nedodělky.
* **8–14 bodů**: Častější výskyt chyb v logice, některé klíčové větve programu nefungují správně, projekt realizuje zadání pouze částečně (chybí některé domluvené funkce) nebo program občas spadne při běžném používání.
* **1–7 bodů**: Zásadní odchylky od zadání (klíčové domluvené funkce zcela chybí), nestabilní aplikace, časté pády (segmentation faults apod.).
* **0 bodů**: Aplikace je zcela nefunkční, vůbec neodpovídá zadání nebo okamžitě po spuštění havaruje.

---

### 3. Architektura, návrh a čistota kódu v C++ (max. 20 bodů)
Tato kategorie hodnotí programátorské řemeslo.
* **20 bodů (Production Ready)**: Kód je na profesionální úrovni (production-ready). Vynikající modularita a čitelnost, rozdělení do `.h`/`.hpp` a `.cpp` souborů. Správa paměti je bezchybná (alokace a dealokace paměti, absence memory leaků a chyb typu use-after-free). OOP principy (zapouzdření, polymorfismus, rozdělení odpovědnosti) jsou použity správně a účelně.
* **15–19 bodů**: Kód je čistý a přehledný, splňuje standardní požadavky na 2. semestr. Objevují se drobná neoptimální architektonická rozhodnutí nebo drobné, málo závažné úniky paměti při ukončení programu. Základní rozdělení do souborů a OOP je zachováno.
* **8–14 bodů**: Kód je špatně strukturovaný, obsahuje příliš dlouhé metody (spaghetti kód), chybí zapouzdření (všechny proměnné veřejné) nebo dochází k závažnějším únikům paměti (např. chybějící destruktory pro dealokaci zdrojů).
* **1–7 bodů**: Zcela chaotický kód (např. vše v jednom obřím souboru), masivní úniky paměti, zneužívání globálních proměnných k obcházení parametrů funkcí.
* **0 bodů**: Kód vykazuje fatální nepochopení jazyka C++ nebo se jedná o plagiát.

---

### 4. Inovace, samostudium a technologie (max. 15 bodů)
Hodnotí se schopnost studenta vyřešit problém kreativně a přinést do projektu nadstandardní prvky.
* **Inovativní přístup**: Body jsou udělovány za technologickou nadstandardnost a kreativitu. Běžné použití prvků standardní knihovny C++ (STL) jako `std::vector` či `std::string` je bráno jako očekávaný standard a samo o sobě nepřináší body.
* **Za co se udělují body**: Bodováno je buď použití nových knihoven (grafika, databáze, GUI, síťová komunikace apod.), nebo inovativní a zajímavé použití standardních prvků (např. vlastní netriviální algoritmy, kreativní vyřešení specifického problému, netriviální práce se šablonami či datovými strukturami). Inovace tedy nemusí pramenit pouze z použití neznámých technologií, ale i z tvůrčího a originálního přístupu k řešení s běžnými nástroji.
* **Omezení pro klišé projekty**: Kopie klasických tutoriálů bez jakékoli přidané hodnoty (např. základní textový Snake, piškvorky v konzoli) jsou penalizovány a nezískají v této kategorii žádné body, pokud student nepřidá výrazný vlastní nápad či rozšíření.

---

### 5. Rozsah a úsilí (max. 15 bodů)
Tato kategorie zohledňuje celkovou pracnost, komplexnost vytvořeného díla a to, zda celkový rozsah odpovídá dohodnutému zadání.
* **Kvalita nad kvantitu**: Projekt nemusí mít tisíce řádků kódu (LOC), aby získal plný počet bodů. Pokud je kód kompaktní, vysoce optimalizovaný, s vysokou hustotou logiky a bez zbytečného balastu, hodnotí se to lépe než uměle nafouknutý kód.
* **11–15 bodů**: Komplexní projekt vyžadující desítky hodin práce, jehož rozsah a úsilí plně odpovídají (nebo převyšují) dohodnutou specifikaci zadání.
* **6–10 bodů**: Středně rozsáhlý projekt s běžnou obtížností a odpovídajícím rozsahem.
* **1–5 bodů**: Velmi triviální projekt (např. jednoduchý CLI skript, který lze napsat za jedno odpoledne) s rozsahem hluboko pod domluveným zadáním.

---

### 6. Prezentace a obhajoba (max. 20 bodů)
Hodnotí se ústní představení projektu, porozumění vlastnímu kódu a schopnost reagovat na dotazy.
* **17–20 bodů**: Student suverénně a bez zaváhání vysvětlí fungování jakékoliv části projektu. Dokáže okamžitě najít a ukázat jednotlivé části kódu v IDE, zdůvodní své architektonické volby, detailně vysvětlí správu paměti (jak alokuje/dealokuje) a bez problémů zodpoví doplňující dotazy.
* **11–16 bodů**: Student kód vysvětlí, ale u složitějších pasáží (např. detaily správy paměti, šablony nebo ukazatele) občas váhá, případně má problém vysvětlit přesné fungování pokročilejších konstruktů.
* **6–10 bodů**: Student vykazuje značnou nejistotu. Kód sice napsal, ale není schopen ho plně obhájit, vysvětlit hlubší logiku nebo má potíže s orientací ve vlastním projektu.
* **1–5 bodů**: Student má extrémní potíže s vysvětlením i základních částí projektu a principů, které v něm použil.
* **0 bodů / Zvláštní upozornění**: Pokud student vůbec nerozumí tomu, jak kód funguje (indikuje to plagiátorství nebo slepé vygenerování pomocí AI bez vlastního přičinění), je celá obhajoba ohodnocena 0 body a projekt je předán k prověření akademické integrity.

---

## Bonusová kategorie (max. +10 bodů)
Bonusové body jsou udělovány za něco mimořádného a nadstandardního. Tato kategorie slouží jako prostor pro vyučujícího k ocenění výjimečně povedených prací na základě implementace něčeho unikátního.

Může jít například o:
* Robustní pokrytí kódu unit testy.
* Nastavení CI/CD pipeline (např. GitHub Actions).
* Pokročilé techniky (multithreading, síťová vrstva, vlastní optimalizace).
* Výjimečně propracované grafické rozhraní nebo herní design.

---

## Pravidla Kalibrace a Integrita (AI & Plagiáty)

1. **Absolutní standard (Junior Developer / Poučený student C++)**: Hodnotí se podle jasně dané kvality kódu, nikoliv pouze porovnáním se zbytkem třídy. Je možné, aby všichni studenti získali 100 %, pokud odevzdají skvělé projekty, stejně jako je možné, že nikdo plného počtu nedosáhne.
2. **AI-Assisted Development**: Použití AI nástrojů (ChatGPT, Claude, Copilot) je povoleno jako pomocník pro vysvětlení chyb či generování šablon. Kód však musí student plně chápat a dodržovat jednotný styl.
