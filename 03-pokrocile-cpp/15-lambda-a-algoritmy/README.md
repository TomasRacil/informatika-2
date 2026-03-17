# 14 - Lambda Funkce a Pokročilé STL Algoritmy

V modulu 13 jsme se podívali na základní kontejnery STL (`vector`, `map`). Nyní se zaměříme na to, co dělá STL tak mocným nástrojem: **algoritmy** a **lambda funkce**.

## 1. Lambda Funkce (Anonymní Funkce)

Představte si, že potřebujete napsat krátkou, jednorázovou funkci, kterou chcete předat jako argument jiné funkci (např. funkci `std::sort` pro vlastní řazení). Definovat kvůli tomu celou novou funkci jinde v kódu je nepraktické.

Lambda funkce (nebo jen "lambda") nám umožňuje definovat funkci přímo v místě jejího použití.

### Základní syntaxe

```cpp
[capture_list](parametry) -> navratovy_typ {
    // tělo funkce
    return ...;
}
```

  * `[]` **Capture list (Seznam zachycení):** Nejdůležitější část. Určuje, které proměnné z okolního *scope* (rozsahu) bude mít funkce k dispozici.
      * `[]`: Nezachytává nic.
      * `[=]`: Zachytává všechny vnější proměnné **hodnotou (kopií)**.
      * `[&]`: Zachytává všechny vnější proměnné **referencí (odkazem)**.
      * `[a, &b]`: Zachytí `a` hodnotou a `b` referencí.
      * `[this]`: Zachytí ukazatel `this` (používá se uvnitř metod třídy).
  * `()` **Parametry:** Stejné jako u běžné funkce.
  * `-> navratovy_typ`: Volitelný. Kompilátor ve většině případů dokáže návratový typ odvodit sám.
  * `{}` **Tělo funkce:** Samotný kód.

### Příklad

```cpp
// Běžná funkce
int secti(int a, int b) {
    return a + b;
}
int vysledek = secti(5, 3);

// Ekvivalentní lambda funkce
// 'auto' se používá, protože typ lambdy je unikátní a generovaný kompilátorem
auto scitani = [](int a, int b) -> int {
    return a + b;
};
int vysledek = scitani(5, 3); // vysledek = 8
```

## 2. STL Algoritmy

Knihovna `<algorithm>` (kterou jsme už viděli u `std::sort`) obsahuje desítky funkcí, které operují na kontejnerech pomocí iterátorů. Lambdy jsou pro ně ideální.

### `std::for_each` (Procházení)

Provede operaci na každém prvku.

```cpp
std::vector<int> v = {1, 2, 3};
// Vypíše každý prvek
std::for_each(v.begin(), v.end(), [](int x) {
    std::cout << x << " ";
});
```

### `std::find_if` (Hledání s podmínkou)

Najde první prvek, který splňuje určitou podmínku.

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
int limit = 3;

// Najde první prvek, který je VĚTŠÍ než 'limit'
auto it = std::find_if(v.begin(), v.end(), [limit](int x) {
    return x > limit; // Zachytili jsme 'limit' hodnotou
});

if (it != v.end()) {
    std::cout << "Prvni prvek > 3 je: " << *it << std::endl; // Vypíše 4
}
```

### `std::count_if` (Počítání s podmínkou)

Spočítá, kolik prvků splňuje podmínku.

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
// Spočítá počet sudých čísel
int pocetSudych = std::count_if(v.begin(), v.end(), [](int x) {
    return (x % 2) == 0;
});
// pocetSudych bude 2 (pro 2 a 4)
```

### `std::transform` (Transformace)

Vytvoří novou kolekci aplikací funkce na každý prvek.

```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2(3); // Cílový vektor musí mít dostatek místa

// Zdvojnásobí každý prvek z v1 a uloží ho do v2
std::transform(v1.begin(), v1.end(), v2.begin(), [](int x) {
    return x * 2;
});
// v2 nyní obsahuje {2, 4, 6}
```

### `std::sort` (Třídění s vlastní logikou)

`std::sort` ve výchozím stavu třídí vzestupně. Pomocí lambdy mu můžeme dát vlastní pravidlo pro porovnání.

```cpp
std::vector<int> v = {1, 5, 2, 9, 7};

// Třídění sestupně
std::sort(v.begin(), v.end(), [](int a, int b) {
    return a > b; // Vrať true, pokud 'a' má být PŘED 'b'
});
// v nyní obsahuje {9, 7, 5, 2, 1}
```

---
## **Cvičení**

### **1. Filtrace**
Máte vektor čísel `{1, 5, 8, 9, 12, 4, 7}`.
Použijte `std::count_if` s lambda funkcí, abyste zjistili, kolik čísel je větších než 6.

### **2. Vlastní řazení**
Máte vektor stringů `{"Jablko", "Banán", "Ananas", "Hruška"}`.
Seřaďte je pomocí `std::sort` **podle délky slova** (od nejkratšího).

### **3. Transformace**
Máte vektor čísel. Pomocí `std::transform` vytvořte nový vektor, který bude obsahovat druhé mocniny čísel z prvního vektoru.
