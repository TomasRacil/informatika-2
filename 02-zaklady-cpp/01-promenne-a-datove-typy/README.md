# **Proměnné a datové typy**

Proměnné jsou základními stavebními kameny každého programu. Slouží jako pojmenované "kontejnery" v paměti počítače, do kterých můžeme ukládat data a později je z nich číst nebo je upravovat.

## **Co je proměnná?**

Každá proměnná v C++ má:

1. **Název (identifikátor):** Jméno, pod kterým k ní přistupujeme (např. `vek`, `jmeno`, `pi`).  
2. **Datový typ:** Určuje, jaký druh dat může proměnná uchovávat a kolik místa si v paměti zabere.  
3. **Hodnotu:** Konkrétní data uložená v proměnné.

## **Základní datové typy**

Datové typy můžeme rozdělit do několika kategorií.

### **Celé číselné typy (Integers)**

Tyto typy uchovávají celá čísla. Mohou být `signed` (znaménkové, tj. kladné i záporné) nebo `unsigned` (bezznaménkové, tj. pouze kladné a nula), což zdvojnásobuje jejich maximální kladnou hodnotu.

| Typ | Velikost (typická) | Rozsah hodnot (pro signed) | Rozsah hodnot (pro unsigned) |
| :---- | :---- | :---- | :---- |
| short | 2 bajty | -32,768 až 32,767 | 0 až 65,535 |
| int | 4 bajty | -2,147,483,648 až 2,147,483,647 | 0 až 4,294,967,295 |
| long | 4 nebo 8 bajtů | Záleží na systému | Záleží na systému |
| long long | 8 bajtů | -9,223,372,036,854,775,808 až ... | 0 až 18,446,744,073,709,551,615 |

### **Desetinné typy (Floating-Point)**

Uchovávají reálná čísla s desetinnou částí.

| Typ | Velikost (typická) | Přesnost |
| :---- | :---- | :---- |
| float | 4 bajty | cca 7 desetinných míst |
| double | 8 bajtů | cca 15 desetinných míst |
| long double | 10 nebo 16 bajtů | Vyšší přesnost než double |

### **Ostatní základní typy**

| Typ | Velikost | Popis a příklad |
| :---- | :---- | :---- |
| char | 1 bajt | Jeden znak, např. 'a', '?' |
| bool | 1 bajt | Logická hodnota true nebo false |
| std::string | Variabilní | Textový řetězec, např. "Ahoj svete" |

*Poznámka: Pro zjištění přesných limitů na vašem systému se používá hlavičkový soubor `<limits>`.*

## **Deklarace a inicializace**

Než můžeme proměnnou použít, musíme ji **deklarovat** – tedy říct kompilátoru její jméno a typ. Poté jí můžeme přiřadit hodnotu, což se nazývá **inicializace**.

```cpp
// Deklarace proměnné 'vek' typu 'int'  
int vek;

// Inicializace (přiřazení hodnoty)  
vek = 25;

// Deklaraci a inicializaci lze provést v jednom kroku  
double pi = 3.14;  
unsigned int pocetObyvatel = 10500000;
```

## **Konstanty**

Pokud chceme zajistit, aby se hodnota proměnné po její inicializaci již nikdy nezměnila, můžeme ji deklarovat jako konstantu pomocí klíčového slova `const`.

```cpp
const double PI = 3.14159;  
// PI = 3.14; // Tento řádek by způsobil chybu při kompilaci  
```
---
## **Cvičení**

### **1. Práce s proměnnými**
Vytvořte program, který:
1. Deklaruje proměnné pro uložení:
   - Vašeho věku (celé číslo).
   - Vaší výšky v metrech (desetinné číslo).
   - Prvního písmene vašeho jména (znak).
   - Zda jste student (logická hodnota).
2. Vypíše tyto hodnoty na obrazovku.
3. Zkuste deklarovat konstantu pro číslo PI a pokuste se ji změnit - sledujte chybovou hlášku kompilátoru.

**Očekávaný výstup:**
```text
Věk: 20
Výška: 1.85
Iniciála: J
Student: 1  (nebo true)
```
