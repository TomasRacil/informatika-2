# 03 - Dynamické datové struktury: Spojový seznam

Zatímco pole (statické i dynamické) ukládá prvky v souvislém bloku paměti, **dynamické datové struktury** propojují jednotlivé prvky pomocí **ukazatelů**. To jim dává větší flexibilitu při vkládání a mazání prvků, i když za cenu pomalejšího přístupu k prvkům podle indexu.

Nejzákladnější dynamickou strukturou je **spojový seznam (linked list)**.

## **Co je Spojový seznam?**

Představte si hledání pokladu, kde každý nalezený lístek obsahuje:
1.  Část pokladu (data).
2.  Nápovědu, kde hledat další lístek (ukazatel na další prvek).

Spojový seznam se skládá z **uzlů (nodes)**. Každý uzel obsahuje:
* **Data:** Hodnota, kterou chceme uložit (např. `int`, `std::string`, objekt...).
* **Ukazatel na další uzel:** Adresa následujícího uzlu v seznamu. U posledního uzlu tento ukazatel ukazuje na `nullptr`.

Seznam jako celek si pak pamatuje pouze **ukazatel na první uzel (hlavu - head)**.

```

[ Head ] ---> [ Uzel 1 | Data: 10 | Next ] ---> [ Uzel 2 | Data: 20 | Next ] ---> [ Uzel 3 | Data: 30 | Next: nullptr ]

```

## **Výhody spojového seznamu (oproti poli)**

* **Dynamická velikost:** Seznam může růst a zmenšovat se podle potřeby za běhu programu. Nemusíme předem znát počet prvků.
* **Efektivní vkládání/mazání:** Vložení nebo smazání prvku *uprostřed* seznamu je velmi rychlé (složitost $O(1)$), pokud už máme ukazatel na předchozí uzel. Stačí jen "přehodit" pár ukazatelů. U pole bychom museli posouvat všechny následující prvky ($O(n)$).

## **Nevýhody spojového seznamu (oproti poli)**

* **Pomalý přístup k prvkům:** Nelze přistoupit k prvku na indexu `i` přímo. Musíme projít seznam od začátku (`head`) a `i`-krát se posunout pomocí ukazatele `next`. Přístup k prvku má složitost $O(n)$.
* **Větší paměťová náročnost:** Každý uzel kromě dat musí uchovávat i ukazatel na další uzel.
* **Složitější správa paměti:** Uzly typicky alokujeme dynamicky (`new`), takže musíme pečlivě dbát na jejich uvolnění (`delete`), abychom předešli únikům paměti.

## **Implementace jednoduchého uzlu**

V C++ se uzel typicky implementuje jako `struct` nebo `class`:

```cpp
struct Uzel {
    int data;       // Data uložená v uzlu
    Uzel* dalsi;    // Ukazatel na následující uzel

    // Konstruktor pro snadné vytváření uzlů
    Uzel(int hodnota) : data(hodnota), dalsi(nullptr) {}
};
```

## **Základní operace**

Nejběžnější operace se spojovým seznamem (pro jednoduchý jednosměrný seznam):

  * **Vytvoření seznamu:** Inicializace ukazatele `head` na `nullptr`.
  * **Vložení na začátek:**
    1.  Vytvoř nový uzel (`new Uzel(...)`).
    2.  Nastav jeho `dalsi` ukazatel na aktuální `head`.
    3.  Přesuň `head` tak, aby ukazoval na nový uzel.
  * **Vložení na konec:**
    1.  Pokud je seznam prázdný, vlož na začátek.
    2.  Jinak projdi seznam až k poslednímu uzlu (ten, jehož `dalsi` je `nullptr`).
    3.  Vytvoř nový uzel.
    4.  Nastav `dalsi` ukazatel posledního uzlu na tento nový uzel.
  * **Výpis seznamu:** Procházej seznam od `head` pomocí dočasného ukazatele, dokud nenarazíš na `nullptr`, a vypisuj data každého uzlu.
  * **Smazání prvku:** (Složitější) Najdi uzel *před* mazaným uzlem, přesměruj jeho `dalsi` ukazatel na uzel *za* mazaným uzlem a pak uvolni paměť mazaného uzlu (`delete`). Speciální případ je mazání prvního uzlu (`head`).
  * **Zrušení seznamu:** Projdi celý seznam a postupně uvolni paměť (`delete`) pro každý uzel.

---
## **Cvičení**

### **1. Manuální spojování**
Použijte strukturu `Uzel` z textu.
1. V `main` dynamicky vytvořte 3 uzly (s daty 1, 2, 3).
2. Manuálně je propojte (ukazatel prvního na druhý, druhého na třetí).
3. Vypište data procházením přes ukazatele ( `head->data`, `head->dalsi->data` ...).
4. Všechny uzly uvolněte (`delete`).

### **2. Výpis cyklem**
Zkuste napsat cyklus `while`, který projde vámi vytvořený seznam a vypíše všechny hodnoty, dokud nenarazí na `nullptr`.
