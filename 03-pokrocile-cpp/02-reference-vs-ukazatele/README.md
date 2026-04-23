# 02 - Reference vs Ukazatele

V této kapitole se podíváme na rozdíly mezi **ukazateli** a **referencemi** v C++. Oba tyto koncepty nám umožňují přistupovat k paměti nepřímo a sdílet data, ale mají odlišná pravidla pro používání.

## **Ukazatele (Pointers)**

Ukazatel je proměnná, která uchovává paměťovou adresu jiné proměnné.

*   **Zápis:** `int* ptr = &hodnota;`
*   Mohou být prázdné (`nullptr`).
*   Mohou být přesměrovány na jinou paměťovou adresu po své inicializaci.
*   K získání nebo úpravě hodnoty, na kterou odkazují, je nutná dereference (pomocí operátoru `*`).

## **Reference**

Reference je jiný název (tzv. "alias") pro již existující proměnnou.

*   **Zápis:** `int& ref = hodnota;`
*   **Musí** být inicializována ihned při svém vytvoření.
*   **Nemůže** být nikdy prázdná (v C++ neexistuje obdoba `nullptr` pro referenci).
*   **Nemůže** být přepojena na jinou proměnnou. Jakmile je reference s něčím svázána, platí to na celý její životní cyklus.
*   Při práci se s ní zachází úplně stejně jako s původní proměnnou (nepoužívá se operátor `*` pro dereferenci).

## **Kdy použít co?**

**Kdy používat reference:**
*   Při předávání parametrů funkcím (tzv. **pass-by-reference**), kdy chceme upravovat původní data nebo se vyhnout zkopírování nadbytečných dat (často u předávání velkých objektů čteme skrze konstantní referenci `const Typ&`).
*   Jejich nasazení je obvykle bezpečnější a kód je lépe čitelný.

**Kdy používat ukazatele:**
*   Pokud je z logiky věci v pořádku, že pointer může ukazovat "na nic" (na `nullptr`).
*   Když potřebujeme měnit cíl ukazatele v průběhu běhu programu.
*   Při práci s dynamickou alokací paměti (`new` a `delete`), při zpracovávání nízkoúrovňových typů dat, nebo když budujeme vlastní dynamické struktury od nuly (jako spojové seznamy a stromy).

---

## **Cvičení**

### **1. Vytvoření a výpis reference**
1. Vytvořte proměnnou `double teplota = 36.6;`.
2. Vytvořte referenci `double& refTeplota` a spárujte ji s proměnnou `teplota`.
3. Změňte hodnotu přes referenci na `37.2` a vypište původní proměnnou `teplota`, abyste si ověřili, že se její hodnota změnila.

### **2. Záludnosti referencí**
Vytvořte dvě proměnné `int a = 10;` a `int b = 20;`.
Následně vytvořte referenci `int& ref = a;`.
- Pokuste se referenci "přesměrovat" pomocí `ref = b;`. 
- Vypište obě proměnné `a` i `b` a zkuste vysvětlit, proč mají obě hodnotu 20 (a že nedošlo k přepojení reference na proměnnou `b`, ale k přiřazení její hodnoty do `a`).

### **3. Funkce a pass-by-reference**
Napište funkci `void prohod(int& x, int& y)`, která vezme dvě čísla a prohodí jejich hodnoty.
- V těle hlavního programu `main` vytvořte `int c = 5;` a `int d = 9;`.
- Zavolejte `prohod(c, d);`.
- Vypište `c` a `d` a ověřte, že `c` je 9 a `d` je 5.
