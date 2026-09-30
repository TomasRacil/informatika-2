# 06 - Úvod do algoritmizace

Tato sekce se věnuje základům algoritmizace. Cílem této části je přestat přemýšlet jen o tom, jak napsat kód, aby fungoval, ale také o tom, jak napsat kód, který je **efektivní**, **škálovatelný** a **dobře navržený**.

Algoritmus je přesný postup nebo sada pravidel pro vyřešení určitého problému. Budeme se učit, jak tyto postupy analyzovat, implementovat a porovnávat jejich efektivitu.

## Struktura sekce

Tato sekce je rozdělena do logických celků pokrývajících teorii, analýzu složitosti i praktickou implementaci.

| Kapitola | Téma | Popis | Stav |
| :--- | :--- | :--- | :---: |
| 1. [Analýza složitosti](./04-analyza-slozitosti/) | Složitost a Big O | Asymptotická časová a prostorová složitost (Big O notace), porovnání tříd složitosti, profilování a měření času v Pythonu (`time.perf_counter`) | Dostupné (C++), *bude doplněn Python* |
| 2. [Řadicí a vyhledávací algoritmy](./01-zakladni-algoritmy/01-radici-algoritmy/) | Řazení a vyhledávání | SelectionSort, BubbleSort, InsertionSort, MergeSort, QuickSort, binární vyhledávání. Porovnání s vestavěným Timsortem (`sorted()`, `list.sort(key=...)`) | Dostupné (C++), *bude doplněn Python* |
| 3. [Rekurze a Backtracking](./01-zakladni-algoritmy/03-rekurze/) | Rekurzivní postupy | Rekurzivní myšlení, princip rozděl a panuj, Hanojské věže, hloubka rekurze (`sys.getrecursionlimit`), technika backtrackingu (problém N dam) | Dostupné (C++), *bude doplněn Python* |
| 4. **Vlastní datové struktury** | Lineární a prioritní struktury | Objektová implementace struktur: Spojový seznam (`LinkedList`, `Node`), Zásobník (`Stack`), Fronta (`Queue` s `collections.deque`), Prioritní fronta a halda (`heapq`) | *Bude doplněno v Pythonu* |
| 5. [Grafové algoritmy](./02-grafove-algoritmy/) | Reprezentace a prohledávání | Reprezentace grafu v Pythonu (seznam sousedů pomocí `dict[str, list[str]]`, matice sousednosti). Prohledávání do šířky (BFS) a hloubky (DFS), detekce cyklů a komponent | Dostupné (C++), *bude doplněn Python* |
| 6. **Hledání nejkratších cest** | Nejkratší cesty | Dijkstrův algoritmus pro ohodnocené grafy (s prioritní frontou `heapq`), hledání cest v bludišti a na mřížce (gridu) | Dostupné (C++), *bude doplněn Python* |
| 7. **Dynamické programování** | Optimalizace a podproblémy | Memoizace shora dolů (dekorátor `@functools.cache`) vs. tabulková metoda zdola nahoru. Úloha batohu, Fibonacci, nejdelší rostoucí podposloupnost | *Bude doplněno v Pythonu* |
| 8. **Praktické algoritmické výzvy** | Soutěžní úlohy | Řešení reálných programátorských výzev (Advent of Code, Codewars styl), efektivní práce s daty a optimalizace | *Bude doplněno v Pythonu* |
