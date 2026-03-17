# **Cykly**

Cykly slouží k opakovanému vykonávání bloku kódu, dokud platí zadaná podmínka. Umožňují nám efektivně zpracovávat velké množství dat nebo opakovat akci bez nutnosti psát stejný kód znovu a znovu.

### **`for` cyklus**

Ideální pro případy, kdy předem víme, kolikrát chceme cyklus opakovat.  
Skládá se ze tří částí oddělených středníky:

1. **Inicializace:** Provede se jednou na začátku (např. `int i = 0`).  
2. **Podmínka:** Testuje se před každou iterací. Pokud je `true`, cyklus pokračuje.  
3. **Inkrementace/Update:** Provede se na konci každé iterace (např. `i++`).

```cpp
for (int i = 1; i <= 5; i++) {  
    std::cout << "Cislo: " << i << std::endl;  
}
```

### **`while` cyklus**

Opakuje blok kódu, dokud je jeho podmínka `true`. Podmínka se testuje **před** každou iterací. Pokud je na začátku `false`, tělo cyklu se neprovede ani jednou.

```cpp
int i = 1;  
while (i <= 5) {  
    std::cout << "Cislo: " << i << std::endl;  
    i++;  
}
```

### **`do-while` cyklus**

Podobný `while` cyklu, ale podmínka se testuje až **na konci** iterace. To zaručuje, že tělo cyklu se provede **minimálně jednou**.

```cpp
int volba;  
do {  
    std::cout << "Zadej cislo (0 pro konec): ";  
    std::cin >> volba;  
} while (volba != 0);
```

### **Řízení běhu cyklu**

* `break`: Okamžitě ukončí celý cyklus (nejen aktuální iteraci). Program pokračuje prvním příkazem za cyklem.  
* `continue`: Ukončí pouze aktuální iteraci a skočí na začátek další iterace, kde se znovu vyhodnotí podmínka.
---
## **Cvičení**

### **1. Malá násobilka**
Pomocí cyklu `for` vypište malou násobilku čísla 5 (5, 10, 15, ..., 50).

### **2. Součet čísel**
Pomocí cyklu `while` nechte uživatele zadávat čísla, dokud nezadá 0. Na konci vypište součet všech zadaných čísel.

### **3. Hádání čísla**
Vytvořte jednoduchou hru, kde program myslí číslo (např. 42) a uživatel hádá.
- Použijte `do-while` cyklus.
- Program bude opakovat výzvu k hádání, dokud uživatel neuhodne správně.
