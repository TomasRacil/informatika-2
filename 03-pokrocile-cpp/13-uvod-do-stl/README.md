# **13 - Úvod do STL (Standard Template Library)**

Standard Template Library (STL) je jádrem standardní knihovny C++. Je to sbírka předpřipravených, vysoce efektivních šablonových tříd a funkcí, které můžete okamžitě použít.

Používání STL je základem moderního C++. Umožňuje psát rychlejší, bezpečnější a čitelnější kód, protože se nemusíte starat o nízkoúrovňové detaily (jako je správa paměti, implementace řadicích algoritmů atd.).

STL má tři hlavní komponenty:

## 1. Kontejnery (Containers)

Kontejnery jsou datové struktury, které ukládají kolekce objektů. Jsou implementovány jako šablony tříd, takže mohou uchovávat jakýkoli datový typ (např. `vector<int>`, `map<string, double>`).

Nejběžnější kontejnery:

* **Sekvenční kontejnery** (udržují pořadí prvků):
    * `std::vector`: Dynamické pole. Rychlý přístup k prvkům (`[]`), rychlé přidávání na konec (`push_back`).
    * `std::deque`: Oboustranná fronta (double-ended queue). Rychlé přidávání/mazání na začátku i na konci.
    * `std::list`: Oboustranně vázaný seznam. Rychlé vkládání/mazání kdekoli uprostřed, ale pomalý přístup k prvkům (nelze použít `[]`).
* **Asociativní kontejnery** (udržují prvky seřazené podle klíče):
    * `std::set`: Ukládá unikátní, seřazené hodnoty. Rychlé vyhledávání, vkládání a mazání (vše $O(log n)$).
    * `std::map`: Ukládá páry klíč-hodnota (jako slovník v Pythonu). Klíče jsou unikátní a seřazené. Rychlé vyhledávání podle klíče ($O(log n)$).
* **Neuspořádané asociativní kontejnery** (používají hashovací tabulky):
    * `std::unordered_set`: Stejné jako `set`, ale prvky nejsou seřazené. Průměrná složitost operací je $O(1)$.
    * `std::unordered_map`: Stejné jako `map`, ale páry nejsou seřazené. Průměrná složitost operací je $O(1)$.

## 2. Iterátory (Iterators)

Iterátor je objekt, který umožňuje procházet prvky v kontejneru. Chová se podobně jako ukazatel – můžeme ho dereferencovat (`*it`) pro získání hodnoty a posouvat (`++it`) na další prvek.

Každý kontejner poskytuje iterátory:
* `kontejner.begin()`: Vrací iterátor na první prvek.
* `kontejner.end()`: Vrací iterátor na místo *za* posledním prvkem (slouží jako zarážka).

```cpp
std::vector<int> v = {10, 20, 30};

// Procházení pomocí iterátoru (starší způsob)
for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " "; // Výpis: 10 20 30
}

// Procházení pomocí range-based for (moderní C++)
// (Tento cyklus na pozadí používá iterátory v.begin() a v.end())
for(int hodnota : v) {
    std::cout << hodnota << " "; // Výpis: 10 20 30
}
```

## 3. Algoritmy (Algorithms)

Knihovna STL (v hlavičce `<algorithm>`) poskytuje obrovské množství funkcí pro práci s kontejnery (nebo obecně s jakýmikoli sekvencemi definovanými iterátory).

  * `std::sort(v.begin(), v.end())`: Seřadí prvky ve vektoru `v`.
  * `std::find(v.begin(), v.end(), 42)`: Hledá hodnotu `42` ve vektoru `v`.
  * `std::reverse(v.begin(), v.end())`: Obrátí pořadí prvků.
  * `std::count(v.begin(), v.end(), 5)`: Spočítá, kolikrát se v kontejneru vyskytuje hodnota `5`.
  * A mnoho dalších (`copy`, `remove`, `transform`, `max_element`, ...).

Používání algoritmů STL je téměř vždy efektivnější a bezpečnější než psaní vlastních cyklů pro tyto operace.

---
## **Cvičení**

### **1. Práce s vektorem**
1. Vytvořte `std::vector<int>`, vložte do něj 10 náhodných čísel.
2. Seřaďte ho pomocí `std::sort`.
3. Vypište ho pomocí range-based for cyklu.

### **2. Slovník**
Vytvořte `std::map<string, int>` reprezentující nákupní seznam (název věci -> počet kusů).
1. Přidejte pár položek (např. "Rohliky" -> 10, "Mleko" -> 2).
2. Zkuste vyhledat, zda seznam obsahuje "Chleba".
3. Vypište celý seznam.

### **3. Unikátní čísla**
Máte pole s duplicitami: `{1, 2, 2, 3, 1, 4}`. Vložte je do `std::set<int>` a vypište výsledek. (Měl by obsahovat jen unikátní čísla).
