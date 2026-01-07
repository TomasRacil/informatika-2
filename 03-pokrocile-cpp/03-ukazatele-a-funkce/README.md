# 03 - Ukazatele a funkce

Ukazatele hrají klíčovou roli při práci s funkcemi v C++. Umožňují nám efektivněji předávat data a dokonce měnit hodnoty proměnných mimo samotnou funkci. Zopakujme si nejprve standardní chování.

## **Předání hodnotou (Pass by Value)**

Toto je **výchozí** způsob předávání argumentů v C++. Když funkci předáte proměnnou, funkce si vytvoří její **lokální kopii**. Jakékoli změny provedené uvnitř funkce ovlivní pouze tuto kopii, **nikoli původní proměnnou**.

```cpp
void nezmeni(int a) {
    a = 100; // Mění se pouze lokální kopie 'a'
}

int main() {
    int x = 10;
    nezmeni(x);
    // x je stále 10
    return 0;
}
```

## **Předání ukazatelem (Pass by Pointer)**

Pokud chceme, aby funkce mohla **změnit původní proměnnou**, můžeme jí místo hodnoty předat **ukazatel (adresu)** na tuto proměnnou. Funkce pak pomocí operátoru dereference (`*`) může přistupovat a modifikovat data na této adrese.

```cpp
void zmeni(int* pA) { // Parametr je ukazatel na int
    *pA = 100; // Měníme hodnotu na adrese, na kterou pA ukazuje
}

int main() {
    int x = 10;
    zmeni(&x); // Funkci předáme ADRESU proměnné x
    // x je nyní 100
    return 0;
}
```

**Výhody:**

  * Umožňuje funkci modifikovat externí proměnné.
  * **Efektivita:** Při předávání velkých objektů (struktur, tříd) je mnohem rychlejší předat jen adresu (ukazatel) než kopírovat celý objekt.

**Nevýhody:**

  * Musíme si dávat pozor na `nullptr`. Pokud funkci předáme nulový ukazatel a pokusíme se ho dereferencovat, program spadne. Je dobré uvnitř funkce kontrolovat platnost ukazatele.

## **Předávání polí funkcím**

Když předáváte C-stylové pole jako argument funkci, dochází k tzv. **rozpadu pole na ukazatel (array decay)**. Funkce ve skutečnosti neobdrží kopii celého pole, ale pouze **ukazatel na jeho první prvek**.

Z tohoto důvodu **musíme funkci vždy předat i velikost pole** jako samostatný argument, protože funkce sama nemá jak zjistit, jak je pole dlouhé.

```cpp
// Funkce přijímá ukazatel na int a velikost
void vypisPole(int* arr, int velikost) {
    for (int i = 0; i < velikost; ++i) {
        // K prvkům můžeme přistupovat pomocí indexů (arr[i])
        // nebo pomocí aritmetiky s ukazateli (*(arr + i))
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Alternativní (a běžný) zápis hlavičky funkce:
// void vypisPole(int arr[], int velikost) { ... }
// Kompilátor to stále chápe jako 'int* arr'

int main() {
    int mojePole[] = {1, 2, 3, 4, 5};
    int n = sizeof(mojePole) / sizeof(mojePole[0]);

    vypisPole(mojePole, n); // Předáme pole (rozpadne se na ukazatel) a jeho velikost
    return 0;
}
```

Protože funkce pracuje s ukazatelem na původní pole, **může pole i modifikovat**.

## **Návrat ukazatele z funkce**

Funkce může také vracet ukazatel. To je často využíváno, když funkce vytváří nějaká data dynamicky na haldě a potřebuje vrátit adresu těchto dat volajícímu kódu.

```cpp
int* vytvorDynamickePole(int velikost) {
    if (velikost <= 0) {
        return nullptr; // Neplatná velikost
    }
    int* pPole = new int[velikost];
    // Můžeme pole i inicializovat...
    for(int i = 0; i < velikost; ++i) {
        pPole[i] = 0;
    }
    return pPole; // Vracíme adresu nově alokovaného pole
}

int main() {
    int* pMojePole = vytvorDynamickePole(10);

    if (pMojePole != nullptr) {
        pMojePole[0] = 100;
        std::cout << "Prvek 0: " << pMojePole[0] << std::endl;

        // VELMI DŮLEŽITÉ: Volající kód je zodpovědný za uvolnění paměti!
        delete[] pMojePole;
        pMojePole = nullptr;
    } else {
        std::cout << "Nepodarilo se alokovat pole." << std::endl;
    }
    return 0;
}
```

**Velké nebezpečí: Vrácení ukazatele na lokální proměnnou\!**

**NIKDY** nevracejte z funkce adresu její lokální proměnné. Lokální proměnné existují pouze na zásobníku a zanikají, jakmile funkce skončí. Vrácený ukazatel by pak ukazoval na neplatnou paměť.

```cpp
int* spatnaFunkce() {
    int lokalniCislo = 50;
    return &lokalniCislo; // CHYBA! Vracíme adresu paměti, která za chvíli zanikne.
}

int main() {
    int* pSpatny = spatnaFunkce();
    // *pSpatny = 10; // Toto je nedefinované chování, program může spadnout nebo dělat nesmysly.
    return 0;
}
```

---
## **Cvičení**

### **1. Prohození čísel (Swap)**
Napište funkci `void prohod(int* a, int* b)`, která prohodí hodnoty dvou proměnných.
- V `main` vytvořte dvě čísla, vypište je, zavolejte funkci a vypište je znovu pro ověření.

### **2. Generator pole**
Napište funkci, která:
- Přijme velikost pole jako argument.
- Dynamicky alokuje pole této velikosti.
- Naplní ho samými nulami.
- Vrátí ukazatel na toto pole.
- (Nezapomeňte v `main` paměť uvolnit!)

### **3. Změna pole**
Vytvořte funkci, která přijme pole (ukazatel a velikost) a všechna čísla v něm vynásobí dvěma.
