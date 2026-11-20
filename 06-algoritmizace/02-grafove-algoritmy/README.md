# 02 - Grafové algoritmy

Grafy jsou základní datové struktury, které modelují vztahy mezi objekty. Skládají se z množiny **vrcholů** (uzlů, *vertices*, značíme $V$) a množiny **hran** (*edges*, značíme $E$), které vrcholy propojují. Využívají se v navigacích (hledání nejkratší trasy), sociálních sítích (přátelství, doporučení), počítačových sítích (směrování paketů), překladačích (závislosti) či plánování úloh.

### Základní pojmy

* **Neorientovaný vs. orientovaný graf:** V neorientovaném grafu je hrana obousměrná (přechod mezi `A` a `B` funguje oběma směry). V orientovaném grafu (*digraf*) má hrana směr `A → B` (např. jednosměrná ulice nebo odkaz na webu).
* **Ohodnocený (vážený) vs. neohodnocený graf:** V ohodnoceném grafu má každá hrana číselnou **váhu** (vzdálenost v km, čas v minutách, cenu). V neohodnoceném grafu mají všechny hrany stejnou „cenu“ 1 krok.
* **Stupeň vrcholu:** Počet hran připojených k vrcholu (u orientovaných rozlišujeme vstupní a výstupní stupeň).
* **Cesta a cyklus:** Cesta je posloupnost vrcholů spojených hranami. Cyklus je cesta, která začíná i končí ve stejném vrcholu.

## Reprezentace grafu v paměti

V paměti počítače nejčastěji reprezentujeme graf dvěma způsoby:

1. **Matice sousednosti (Adjacency Matrix):**
   * 2D pole rozměru $V \times V$, kde `matice[i][j] == 1` (případně váha hrany) znamená, že existuje hrana z `i` do `j`.
   * **Výhoda:** Zjištění, zda existuje hrana mezi dvěma vrcholy, trvá $O(1)$.
   * **Nevýhoda:** Paměťová složitost je vždy $O(V^2)$, což je neefektivní pro velké **řídké grafy** (např. silniční síť s miliony křižovatek, kde každá vede jen do pár dalších).
2. **Seznam sousednosti (Adjacency List):**
   * Každý vrchol má uložen pouze seznam svých přímých sousedů (v C++ např. `std::map<int, std::vector<Edge>>`, v Pythonu `dict[int, list[Hrana]]`).
   * **Výhoda:** Paměťová složitost je pouze $O(V + E)$ a procházení sousedů vrcholu je velmi rychlé.
   * **Nevýhoda:** Zjištění existence konkrétní hrany $(u, v)$ vyžaduje projití sousedů vrcholu $u$, tedy $O(\deg(u))$.

## BFS (Breadth-First Search) – Prohledávání do šířky

BFS prohledává graf po „vrstvách“ podle vzdálenosti (počtu hran) od startovního vrcholu. Nejprve navštíví startovní vrchol (vrstva 0), poté všechny jeho přímé sousedy (vrstva 1), pak sousedy sousedů (vrstva 2) atd.

* **Datová struktura:** **Fronta (Queue)** – FIFO (*First In, First Out*, v Pythonu `collections.deque`).
* **Postup:**
  1. Vlož `start` do fronty a ihned ho označ jako navštívený.
  2. Dokud fronta není prázdná, odeber vrchol `u` ze začátku fronty.
  3. Projdi všechny nenavštívené sousedy `v` vrcholu `u`, označ je jako navštívené (aby se do fronty nedostaly vícekrát) a vlož je na konec fronty.
* **Proč zaručuje nejkratší cestu:** Díky průchodu po vrstvách platí, že jakmile na cíl narazíme poprvé, cesta k němu má zaručeně nejmenší možný počet hran.
* **Využití:** Nejkratší cesta v **neohodnoceném** grafu, hledání v bludišti, šíření signálu / nákazy, web crawling.
* **Složitost:** Časová $O(V + E)$, paměťová $O(V)$.

## DFS (Depth-First Search) – Prohledávání do hloubky

DFS se snaží jít vždy co nejdále po jedné větvi, dokud nenarazí na slepý konec nebo již navštívený vrchol. Teprve poté se vrací (*backtracking*) na poslední křižovatku a zkouší další větev.

* **Datová struktura:** **Zásobník (Stack)** – LIFO (*Last In, First Out*), případně **Rekurze** (která využívá zásobník volání funkcí).
* **Postup:**
  1. Označ aktuální vrchol `u` jako navštívený.
  2. Pro každého nenavštíveného souseda `v` rekurzivně zavolej DFS (nebo ho vlož na zásobník).
* **Vlastnosti:** DFS **nezaručuje** nalezení nejkratší cesty, ale má menší paměťové nároky u hlubokých grafů a přirozeně prozkoumává celé větve.
* **Využití:** Detekce cyklů v grafu, topologické řazení (např. pořadí kompilace/závislostí), hledání komponent souvislosti, generování všech cest.
* **Složitost:** Časová $O(V + E)$, paměťová $O(V)$.

## Dijkstrův algoritmus

Slouží k nalezení nejkratší cesty v **ohodnoceném** grafu, kde mají hrany různé **váhy** (např. délku silnice, čas průchodu, cenu).

* **Nutná podmínka:** Váhy všech hran musí být **nezáporné** ($\ge 0$). Pokud by existovala záporná hrana, hladová volba nejbližšího vrcholu by mohla selhat (pro záporné hrany se používá např. Bellmanův–Fordův algoritmus).
* **Datová struktura:** **Prioritní fronta** (`std::priority_queue` v C++, `heapq` v Pythonu), která vždy efektivně vybere vrchol s nejmenší dosud známou vzdáleností.
* **Princip (Relaxace hran):**
  1. Vzdálenost ke `start` nastav na `0`, ke všem ostatním vrcholům na `∞`.
  2. Z prioritní fronty vyber vrchol `u` s nejmenší vzdáleností `d`. (Pokud je `d` větší než již známá nejlepší vzdálenost do `u`, záznam přeskoč.)
  3. Pro každou odchozí hranu $(u, v)$ s vahou $w$ ověř, zda cesta přes `u` není kratší: pokud $d + w < \text{vzd}[v]$, aktualizuj $\text{vzd}[v] = d + w$, zapamatuj si předchůdce `pred[v] = u` a vlož `(vzd[v], v)` do prioritní fronty.
* **Složitost:** Časová $O((V + E) \log V)$ (pro souvislé grafy zjednodušeně $O(E \log V)$), paměťová $O(V + E)$.

---

### Přehledové srovnání algoritmů

| Algoritmus | Datová struktura | Váhy hran | Zaručuje nejkratší cestu? | Časová složitost | Typické použití |
| :--- | :--- | :---: | :---: | :---: | :--- |
| **BFS** | Fronta (`deque`) | Neohodnocený | **Ano** (počet hran) | $O(V + E)$ | Nejkratší cesta v bludišti, úrovně |
| **DFS** | Zásobník / Rekurze | Libovolné | **Ne** | $O(V + E)$ | Cykly, topologické řazení, všechny cesty |
| **Dijkstra** | Prioritní fronta (`heapq`) | Nezáp. ($\ge 0$) | **Ano** (součet vah) | $O(E \log V)$ | Navigace, mapy, síťové směrování |

---

### Srovnání průchodu

Představte si, že hledáte někoho v budově:
* **BFS:** Prohledáte celé přízemí, pak celé první patro, pak celé druhé patro...
* **DFS:** Vběhnete do prvních dveří, běžíte chodbou až na konec, pak do schodů až na půdu, a když narazíte na zeď, vracíte se o křižovatku zpět.

---

## Cvičení k procvičení

1. **Neorientovaný graf a stupeň vrcholů:**
   Upravte třídu `Graf` tak, aby podporovala parametr `orientovany: bool = True` v konstruktoru. Přidejte metodu `stupen_vrcholu(vrchol)`, která vrátí počet sousedů daného vrcholu.
2. **Nejkratší cesta v neohodnoceném grafu (BFS):**
   Rozšiřte metodu `bfs` tak, aby přijímala i cílový vrchol `cil` a vrátila konkrétní nejkratší cestu (seznam vrcholů od `start` po `cil`), případně `None`, pokud cesta neexistuje.
3. **Detekce dosažitelnosti / cyklu (DFS):**
   Napište pomocí DFS metodu `je_dosazitelny(start, cil) -> bool`, která ověří, zda z vrcholu `start` vede cesta do `cil`.
4. **Dijkstrův algoritmus pro mapu měst:**
   Vytvořte graf s textovými názvy měst (např. `"Praha"`, `"Brno"`, `"Ostrava"`, `"Plzeň"`) a vzdálenostmi v km. Najděte nejkratší trasu mezi dvěma vybranými městy.