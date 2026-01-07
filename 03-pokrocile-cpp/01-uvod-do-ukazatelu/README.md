# **01 - Úvod do ukazatelů (Pointers)**

Ukazatele jsou jedním z nejsilnějších a zároveň nejobávanějších konceptů v C++. Jsou to proměnné, jejichž hodnotou není přímo datový typ (jako `int` nebo `double`), ale **adresa v paměti**, kde jsou uložena jiná data.

Můžeme si je představit jako adresu v adresáři. Místo toho, abychom u sebe nosili celý dům (objekt), nosíme u sebe jen lístek s jeho adresou.

![alt pointer ilustration](https://hackingcpp.com/cpp/lang/pointers1.svg)

## **Proč používat ukazatele?**

1.  **Dynamická alokace paměti:** Umožňují nám vytvářet proměnné a pole za běhu programu, jejichž velikost nemusíme znát při kompilaci (viz `new` a `delete`).
2.  **Efektivní předávání funkcím:** Místo kopírování velkých objektů (což je pomalé) můžeme funkci předat pouze ukazatel (adresu) na tento objekt.
3.  **Práce s poli:** Ukazatele a pole jsou v C++ velmi úzce spjaty.
4.  **Polymorfismus:** Jsou klíčové pro implementaci objektově orientovaného polymorfismu.

---

## **Základní operace**

Pro práci s ukazateli potřebujeme znát tři speciální operátory:

### **1. Deklarace ukazatele (`*`)**

Ukazatel deklarujeme pomocí hvězdičky (`*`) mezi typem a názvem proměnné. Tím říkáme: "Tato proměnná neuchovává `int`, ale adresu, kde je `int` uložen."

```cpp
int* pCislo;     // Ukazatel na celé číslo (písmeno 'p' je běžná konvence)
double* pPrumer; // Ukazatel na desetinné číslo
char* pZnak;     // Ukazatel na znak
```

**Důležité:** V tuto chvíli ukazatel `pCislo` nikam neukazuje. Obsahuje náhodnou (neinicializovanou) adresu, což je nebezpečné.

### **2. Operátor adresy (`&`)**

Tento operátor vrátí paměťovou adresu existující proměnné.

```cpp
char c = 65;
char* p;

p = &c; // Do ukazatele 'p' ulož adresu proměnné 'c'
```

Nyní `p` "ukazuje" na `c`.

![alt pointer ilustration](https://hackingcpp.com/cpp/lang/pointer1.svg)

### **3. Operátor dereference (`*`)**

Tento operátor nám umožňuje "jít na adresu" uloženou v ukazateli a přečíst nebo zapsat hodnotu, která se na té adrese nachází.

*Ano, hvězdička se používá pro deklaraci i dereferenci. Kompilátor pozná rozdíl podle kontextu.*

```cpp
char c = 88; // hodnota 88 - 'X'
char* p;

// Čtení hodnoty
char x = *pVek; // hodnota bude 88 - 'X'
std::cout << *x;  // Vypíše X

// Zápis hodnoty
*p = 89;          // Na adresu uloženou v 'p' zapiš hodnotu 89 - 'Y'
std::cout << c;    // Vypíše Y (změnili jsme 'c' nepřímo!)
```

![alt pointer ilustration](https://hackingcpp.com/cpp/lang/pointer2.svg)


-----

## **Nulový ukazatel (`nullptr`)**

Pokud chceme, aby ukazatel záměrně nikam neukazoval (např. při inicializaci), přiřadíme mu klíčové slovo `nullptr`. Je to bezpečná hodnota, kterou můžeme testovat. V starších kódech můžete vidět makro `NULL`, ale v moderním C++ se vždy preferuje `nullptr`.

```cpp
int* pData = nullptr;

if (pData != nullptr) {
    // Pracuj s daty
} else {
    std::cout << "Ukazatel je neplatný." << std::endl;
}
```

-----

## **Ukazatele a pole**

V C++ je název pole v podstatě **konstantní ukazatel** na první prvek tohoto pole.

```cpp
int cisla[5] = {10, 20, 30, 40, 50};

int* pPole = cisla; // NENÍ potřeba operátor '&'
// pPole nyní ukazuje na adresu prvního prvku (cisla[0])

std::cout << *pPole; // Vypíše 10
```

### **Aritmetika s ukazateli**

S ukazateli můžeme provádět omezené aritmetické operace. Nejběžnější je přičítání a odčítání.

  * `pPole + 1` neposune adresu o 1 bajt, ale posune ji o velikost datového typu, na který ukazuje (v našem případě o `sizeof(int)`, tedy typicky 4 bajty). Dostaneme tak adresu **dalšího prvku** v poli.

```cpp
int cisla[3] = {10, 20, 30};
int* pPole = cisla;

// cisla[0]
std::cout << *pPole; // Vypíše 10

// cisla[1]
pPole++; // Posune ukazatel na další prvek
std::cout << *pPole; // Vypíše 20

// cisla[2]
std::cout << *(pPole + 1); // Vypíše 30 (ukáže na další prvek bez změny pPole)
```

Zápisy `pole[i]` a `*(pole + i)` jsou pro kompilátor ekvivalentní.

-----

## **Ukazatele a funkce**

Toto je jedna z nejdůležitějších aplikací ukazatelů. Standardně C++ předává argumenty funkcím **hodnotou (by value)**, což znamená, že funkce pracuje s lokální kopií.

Pokud ale funkci předáme **ukazatel (adresu)**, můžeme přímo měnit původní proměnnou mimo funkci.

```cpp
// 1. Předání hodnotou (funkce dostane KOPII)
void nezmeniHodnotu(int x) {
    x = 100; // Mění se pouze lokální kopie x
}

// 2. Předání ukazatelem (funkce dostane ADRESU)
void zmeniHodnotu(int* pX) {
    *pX = 100; // Měníme hodnotu na adrese, kterou jsme dostali
}

int main() {
    int cislo = 5;
    
    nezmeniHodnotu(cislo);
    // cislo je stále 5
    
    zmeniHodnotu(&cislo); // Funkci předáme ADRESU proměnné
    // cislo je nyní 100
}
```

-----

## **Void ukazatel (`void*`)**

`void*` je speciální typ ukazatele, který může ukázat na **jakýkoliv datový typ**. Je to "obecný" ukazatel.

  * **Nevýhoda:** Protože neznáme typ, nemůžeme ho přímo dereferencovat (`*pVoid`) ani na něj aplikovat aritmetiku (`pVoid++`).
  * **Použití:** Musíme ho nejprve **přetypovat** (`static_cast`) na konkrétní typ ukazatele.

```cpp
int hodnota = 5;
void* pVoid = &hodnota;

// std::cout << *pVoid; // CHYBA: nelze dereferencovat void*

// Přetypujeme void* na int* a pak dereferencujeme
int* pInt = static_cast<int*>(pVoid);
std::cout << *pInt; // Vypíše 5
```


---
## **Cvičení**

### **1. Základy**
1. Vytvořte proměnnou `int cislo = 10;`.
2. Vytvořte ukazatel `int* pCislo` a nasměrujte ho na proměnnou `cislo`.
3. Vypište adresu proměnné `cislo` a hodnotu, kterou obsahuje, pomocí ukazatele.

### **2. Změna hodnoty**
Pomocí ukazatele `pCislo` změňte hodnotu v proměnné `cislo` na 20. Ověřte výpisem původní proměnné.

### **3. Aritmetika**
Vytvořte pole `int cisla[] = {10, 20, 30};`.
- Vytvořte ukazatel na začátek pole.
- Pomocí posouvání ukazatele (aritmetiky) vypište všechny tři hodnoty.
