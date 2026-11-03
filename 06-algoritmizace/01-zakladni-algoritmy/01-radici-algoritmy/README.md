# Třídicí algoritmy

Tento dokument shrnuje základní pojmy týkající se třídění dat a popisuje principy vybraných třídicích algoritmů.

## Základní pojmy

* **Třídění:** Proces uspořádání prvků v určitém pořadí (např. vzestupně, sestupně) podle daného kritéria.
* **Setříděná posloupnost:** Posloupnost prvků, které jsou uspořádány podle daného kritéria.

### Stabilita třídění

Stabilita třídicího algoritmu určuje, jak se algoritmus chová k prvkům se stejným klíčem (hodnotou, podle které se třídí).

* **Stabilní algoritmus:** Zachovává původní relativní pořadí stejných prvků.
    * **Příklad:** Máme seznam studentů seřazený podle jména. Pokud je seřadíme stabilním algoritmem podle věku, studenti se stejným věkem zůstanou seřazeni podle abecedy.
* **Nestabilní algoritmus:** Nemusí zachovat původní pořadí stejných prvků.
    * **Příklad:** Při použití nestabilního algoritmu na stejném seznamu studentů by se studenti se stejným věkem mohli objevit v libovolném pořadí.

> **Proč je stabilita důležitá?**
>
> Stabilita je důležitá v situacích, kdy data již byla setříděna podle jednoho kritéria a chceme je setřídit podle dalšího kritéria, aniž bychom narušili původní pořadí.

### Složitost algoritmu

Složitost algoritmu vyjadřuje jeho efektivitu. Měří se z hlediska:

* **Časové složitosti:** Udává, jak dlouho algoritmus trvá v závislosti na velikosti vstupních dat (např. počet prvků v poli).
* **Prostorové složitosti:** Udává, kolik paměti algoritmus spotřebuje v závislosti na velikosti vstupních dat.

#### Notace "velké O"

Složitost se obvykle vyjadřuje pomocí notace "velké O", která popisuje horní hranici růstu funkce. Budeme se jí věnovat detailně v sekci `04-analyza-slozitosti/`. Prozatím si vystačíme se základním přehledem:

* **O(1):** Konstantní složitost - čas/paměť se nemění s velikostí dat.
* **O($\log n$):** Logaritmická složitost - velmi efektivní, čas roste extrémně pomalu.
* **O(n):** Lineární složitost - čas roste přímo úměrně velikosti dat.
* **O($n \log n$):** Lineárně-logaritmická složitost - velmi efektivní pro třídicí algoritmy.
* **O($n^2$):** Kvadratická složitost - neefektivní, čas roste s druhou mocninou velikosti dat.

---

## Třídicí algoritmy

### 1. Selection sort (třídění výběrem)

**Princip:**
1.  Algoritmus prochází nesetříděnou část pole a hledá v ní nejmenší prvek.
2.  Nalezený nejmenší prvek prohodí s prvním prvkem nesetříděné části.
3.  Tím se první prvek stává součástí setříděné části pole.
4.  Algoritmus se opakuje pro zbytek nesetříděné části, dokud není celé pole setříděné.

**Ilustrace:**

![alt selection sort ilustration](https://tutorialhorizon.com/static/media/algorithms/2019/01/Selection-Sort-Gif.gif)

**Vlastnosti:**
* **Časová složitost:** $O(n^2)$
* **Stabilita:** Nestabilní
* **Využití:** Jednoduchá implementace, vhodný pro výuku, ale neefektivní pro velká data.

### 2. Bubble sort (bublinkové třídění)

**Princip:**
1.  Algoritmus prochází pole a porovnává sousední prvky.
2.  Pokud jsou sousední prvky v nesprávném pořadí, prohodí je.
3.  Tímto způsobem se "bublají" větší prvky směrem ke konci pole.
4.  Algoritmus opakuje procházení pole, dokud nejsou všechny prvky na svém místě.

**Ilustrace:**

![alt bubble sort ilustration](https://upload.wikimedia.org/wikipedia/commons/c/c8/Bubble-sort-example-300px.gif)

**Vlastnosti:**
* **Časová složitost:** $O(n^2)$
* **Stabilita:** Stabilní
* **Využití:** Pouze pro výuku, jeden z nejpomalejších algoritmů.

### 3. Insertion sort (třídění vkládáním)

**Princip:**
1.  Algoritmus si představí pole rozdělené na seřazenou (na začátku jen 1. prvek) a neseřazenou část.
2.  Postupně bere prvky z neseřazené části.
3.  Každý prvek "vloží" na správné místo v již seřazené části tím, že posouvá větší prvky doprava, aby mu uvolnily místo.

**Ilustrace:**

![alt insertion sort ilustration](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)

**Vlastnosti:**
* **Časová složitost:** $O(n^2)$
* **Stabilita:** Stabilní
* **Využití:** Velmi efektivní pro malá data nebo pro *téměř seřazená* data (v nejlepším případě $O(n)$).

### 4. Merge sort (třídění sléváním)

**Princip:** (Paradigma "Rozděl a panuj")
1.  **Rozděl:** Pole se rekurzivně rozděluje na poloviny, dokud nezískáme podpole o jednom prvku (triviálně setříděné).
2.  **Panuj (Slučuj):** Setříděná podpole se postupně slučují (merge) do větších setříděných polí. Slučování probíhá tak, že se porovnávají prvky z obou polí a menší z nich se vloží do výsledného pole.

**Ilustrace:**

![alt merge sort ilustration](https://upload.wikimedia.org/wikipedia/commons/c/cc/Merge-sort-example-300px.gif)

**Vlastnosti:**
* **Časová složitost:** $O(n \log n)$ (zaručená, i v nejhorším případě)
* **Stabilita:** Stabilní
* **Využití:** Velmi efektivní a spolehlivý. Nevýhodou je vyšší prostorová složitost, protože potřebuje pomocné pole o velikosti $O(n)$ pro slévání.

### 5. Quick sort (rychlé třídění)

**Princip:** (Paradigma "Rozděl a panuj")
1.  **Vyber pivot:** Z pole se vybere jeden prvek, tzv. pivot (často první, poslední nebo náhodný).
2.  **Rozděl (Partition):** Pole se přeuspořádá tak, že všechny prvky menší než pivot jsou vlevo od něj a všechny prvky větší (nebo rovné) jsou vpravo od něj. Pivot je tím na své finální pozici.
3.  **Panuj (Rekurze):** Obě části (levá a pravá od pivota) se rekurzivně třídí stejným způsobem.

**Ilustrace:**

![alt quicksort (hoare) ilustration](https://upload.wikimedia.org/wikipedia/commons/9/9c/Quicksort-example.gif)

**Vlastnosti:**
* **Časová složitost:** Průměrná $O(n \log n)$, nejhorší případ $O(n^2)$ (při špatné volbě pivota, např. na již seřazeném poli).
* **Stabilita:** Nestabilní
* **Využití:** V praxi často nejrychlejší algoritmus. Řadí "na místě" (nepotřebuje další pole).

