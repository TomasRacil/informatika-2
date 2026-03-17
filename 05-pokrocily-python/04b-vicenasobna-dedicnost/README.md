# **04b - Vícenásobná dědičnost a MRO**

Python, na rozdíl od některých jiných jazyků (např. C# nebo Java), podporuje **vícenásobnou dědičnost**. To znamená, že třída může mít více nežnoho rodiče.

```
class Dite(Otec, Matka):  
    pass
```

Ačkoliv je to silný nástroj, přináší komplikace, zejména tzv. **Diamantový problém**.

## **1. Diamantový problém (Diamond Problem)**

Představte si hierarchii tvaru diamantu:

1. Třída `A` (kořen).  
2. Třídy `B` a `C` dědí z `A`.  
3. Třída `D` dědí z `B` i `C`.

![Diamantový problém](https://d14qv6cm1t62pm.cloudfront.net/ccbp-website/Blogs/home/diamond-problem-in-java-explained-with-examples-and-solutions-image-1.png)

Otázka: Pokud zavoláme metodu (např. `__init__`) na třídě `D`, a ta zavolá rodiče... kolikrát se spustí `__init__` třídy `A`?  
Pokud bychom volali rodiče "klasicky" (`B.__init__` a `C.__init__`), třída `A` by se inicializovala dvakrát. To je chyba (představte si dvojí připojení k databázi nebo dvojí odečtení peněz).

## **2. Řešení: `super()` a MRO**

Python řeší tento problém pomocí **MRO (Method Resolution Order)** a funkce `super()`.

### **Co je MRO?**

MRO je seznam (pořadí), ve kterém Python hledá metody. Je to linearizace grafu dědičnosti.  
Pro třídu `D` výše by MRO vypadalo takto: `[D, B, C, A, object]`.  
MRO si můžete zobrazit pomocí metody `.mro()`:

```python
print(D.mro())
```

### **Jak funguje `super()` v kontextu MRO?**

`super()` nevolá třídu rodiče, ale volá další třídu v řadě podle MRO.  
V našem diamantu:

1. `D` zavolá `super().__init__()` -> MRO říká, že po `D` následuje `B`. Zavolá se `B`.  
2. `B` zavolá `super().__init__()` -> MRO říká, že po `B` následuje `C` (nikoliv `A`!). Zavolá se `C`.  
3. `C` zavolá `super().__init__()` -> MRO říká, že po `C` následuje `A`. Zavolá se `A`.  
4. `A` zavolá `super().__init__()` -> Konec řetězce (object).

Díky tomu se každá metoda zavolá **právě jednou**. Tomu se říká **kooperativní vícenásobná dědičnost**. Aby to fungovalo, musí **všechny** třídy v hierarchii používat `super()`, i když dědí jen z `object`.
---
## **Cvičení**

### **1. MRO Průzkumník**
Vytvořte "diamantovou" strukturu tříd:
- `A` s metodou `pozdrav()` ("Ahoj z A").
- `B(A)` přepíše `pozdrav` ("Ahoj z B") a zavolá `super`.
- `C(A)` přepíše `pozdrav` ("Ahoj z C") a zavolá `super`.
- `D(B, C)` přepíše `pozdrav` ("Ahoj z D") a zavolá `super`.

Vytvořte instanci `D` a zavolejte `pozdrav()`. Sledujte pořadí výpisů.
