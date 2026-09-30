# **Výuka Informatiky 1 a 2 – Úvodní hodina**

Tento repozitář slouží jako hlavní rozcestník pro předměty **Informatika 1** (2. semestr) a **Informatika 2** (3. semestr). V rámci těchto předmětů se společně ponoříme do světa programování ve dvou silných a široce používaných jazycích: C++ a Python.

## **1. Cíle předmětu**

Cílem obou předmětů je:
* **Naučit se přemýšlet jako programátor:** Osvojit si algoritmické myšlení a principy řešení problémů.
* **Zvládnout základy programování:** Porozumět nízkoúrovňovým konceptům, správě paměti a objektovému programování v C++ a rychlému vývoji s rozsáhlým ekosystémem knihoven v Pythonu.
* **Získat praktické dovednosti:** Veškerou teorii si vyzkoušet na praktických úkolech a větších projektech.
* **Osvojit si moderní nástroje:** Pracovat s verzovacím systémem Git a kontejnerizací pomocí Dockeru pro efektivní vývoj (primárně v Informatice 2).

Po absolvování kurzů byste měli být schopni samostatně navrhnout a implementovat funkční aplikace a znát rozdíly i výhody využití jednotlivých jazyků.

---

## **2. Informatika 1 (2. semestr)**

Tento předmět je zaměřen převážně na jazyk **C++** s menší sekcí věnovanou jazyku **C#**, kterou bude učit kolega.

### **Způsob udělení zápočtu**
Zápočet bude udělen za aktivní účast a především za odevzdání průběžné práce a projektů.
* **Splnění požadavků kolegy** (v rámci sekce C#).
* **Vlastní projekt v C++:** Odevzdání samostatného projektu demonstrujícího získané dovednosti.
* **Průběžné testy:** Celkem jich bude zadáno 6. K zápočtu z nich musíte dosáhnout průměrného hodnocení **nad 50 %**.

### **Zkouška a hodnocení**
Výslednou známku z předmětu **rozhoduje pouze zkouška** (skládá se z praktické a ústní části). Minimální hranice pro úspěšné složení zkoušky je **nad 60 %**.

* **Proč projekt a testy nepřináší body ke zkoušce?**  
  Z prostého důvodu: většina studentů by pro vytvoření projektu pouze využila LLM (AI generátory kódu). Projekt proto slouží výhradně k procvičení a jako **podmínka pro zápočet** (kde se při obhajobě ověří vaše porozumění kódu). K samotné zkoušce se za ně žádné body nepřičítají.
* **Plusové body v průběhu semestru:**  
  Během semestru budou vypsány příležitosti, jak získat **plusové body ke zkoušce** (např. za aktivitu ve výuce, proaktivní přístup či dobrovolné bonusové výzvy). Tyto body se započítávají až po úspěšném složení zkoušky (překročení minima 60 %) a mohou vylepšit vaši výslednou známku.

---

## **3. Informatika 2 (3. semestr)**

Podmínky fungují na stejném principu a předmět je zaměřen na jazyk **Python**.

### **Způsob udělení zápočtu**
* **Povinné domácí úkoly (Git/GitHub):** Místo testů se budou úkoly (9 až 12 úkolů) vypracovávat přes GitHub formou Pull Requestů. Všechny úkoly jsou **povinné pro udělení zápočtu a musí být odevzdány v termínu**.
* **Vlastní projekt v Pythonu:** Odevzdání a obhajoba projektu je **klíčovou podmínkou k zapsání zápočtu**. Bez obhájeného projektu nelze zápočet udělit.

### **Zkouška a hodnocení**
Stejně jako u Informatiky 1 rozhoduje o výsledné známce **pouze zkouška** (minimum pro splnění je **nad 60 %**).
* **Žádné body za projekt a úkoly ke zkoušce:** Z důvodu snadného zneužití LLM slouží projekt a úkoly čistě pro zápočet a k praktickému osvojení látky.
* **Plusové body:** V průběhu semestru bude možné získat plusové body (za aktivní přístup ve výuce, bonusové miniprojekty či výzvy), které mohou vylepšit známku po splnění zkouškového minima.

---

## **4. Klasifikace (Společná)**

U obou předmětů platí následující klasifikační stupnice (k zisku ze zkoušky po započtení případných plusových bodů):

* **A:** > 92 %
* **B:** > 84 %
* **C:** > 76 %
* **D:** > 68 %
* **E:** > 60 %

Příklad: *Představme si, že získáte ze zkoušky 62 % (což odpovídá známce E). Pokud jste během semestru získali například +15 % plusových bodů za aktivitu a bonusové výzvy, výsledné hodnocení bude 77 %, což vám vylepší známku na C.*

---

## **5. Úvod do vyučovaných jazyků**

### **Proč zrovna tyto jazyky?**
Kombinace C++ a Pythonu pokrývá obrovské spektrum programátorských úloh. Zatímco C++ exceluje ve výkonu a kontrole nad hardwarem, Python nabízí neuvěřitelnou rychlost vývoje a jednoduchost.

#### **C++**

* **Charakteristika:** Kompilovaný jazyk, extrémní rychlost, efektivita, plná kontrola nad hardwarem a správou paměti.
* **Kdy ho použít:**  
  * Aplikace kritické na výkon (hry, grafické editory, vědecké výpočty).  
  * Systémové programování (operační systémy, ovladače).  
  * Vestavěné systémy (Embedded systémy, IoT).  
  * Síťové programování.  
* **Nevýhody:** Složitější syntaxe, strmější křivka učení.
```cpp
#include <iostream>

int main() {  
    std::cout << "Hello, C++ World!";  
    return 0;  
}
```

#### **Python**

* **Charakteristika:** Interpretovaný jazyk, velmi jednoduchá a čitelná syntaxe, obrovské množství knihoven.  
* **Kdy ho použít:**  
  * Rychlý vývoj a prototypování.  
  * Webový vývoj (backend).  
  * Analýza dat, strojové učení a umělá inteligence.  
  * Skriptování a automatizace úloh.  
* **Nevýhody:** Nižší výkon v porovnání s C++.
```python
print('Hello, Python world!')
```

## **6. Nástroje a prostředí**

Pro tento kurz budeme používat moderní a standardní nástroje, které vám usnadní práci a připraví vás na praxi. Většinu moderních agilních nástrojů si nejvíc užijeme v navazující Informatice 2.

* **Primární nástroje:**
  * **Git & GitHub:** Pro verzování, sdílení kódu a odevzdávání úkolů (hlavní náplň v Info 2).
  * **Docker & Docker Compose:** Pro zajištění stejného vývojového prostředí všem beze strachu, že "u mě to funguje" (primárně v Info 2).
  * **VS Code:** Doporučený editor s rozšířeními pro C++ a Python.

---

## **7. Spuštění vývojového prostředí (Dev Container v Info 2)**

Celý repozitář je připraven jako **Dev Container**. To znamená, že nemusíte nic složitě instalovat na svůj počítač. Stačí mít **Docker Desktop** a **VS Code** s rozšířením **"Dev Containers"**.

**Postup spuštění:**

1. **Otevřete složku projektu ve VS Code.**
2. VS Code automaticky detekuje konfiguraci a v pravém dolním rohu zobrazí notifikaci s tlačítkem **"Reopen in Container"**. Klikněte na něj.
3. Počkejte, až se kontejner sestaví a spustí. VS Code se k němu automaticky připojí.
4. Nyní můžete otevřít terminál přímo ve VS Code (Terminal -> New Terminal). Tento terminál již běží uvnitř kontejneru a máte v něm k dispozici kompilátor pro C++ (g++), interpret Pythonu (python3) a všechny ostatní potřebné nástroje.

---

## **8. Motivační příklad**
Abychom viděli rozdíly mezi jazyky v praxi, podívejte se na jednoduchý [**motivační příklad**](./motivacni-priklad/README.md), který řeší stejnou úlohu (načtení a součet čísel ze souboru) jednou v C++ a jednou v Pythonu.

---

## **9. Harmonogram a Co dál?**

* **Harmonogram:** Aktuální a detailní plán výuky (napříč týdny) je dostupný v [**detailním harmonogramu semestru**](./harmonogram-2026-2027ZS.md). Harmonogram je orientační. Materiály, úkoly a příklady k nim budou postupně přidávány a zpřístupňovány.
* **Pro studenty obou předmětů (Skupinová spolupráce):** Během první nebo druhé hodiny proběhne rozdělení do znalostně vyrovnaných skupin. V průběhu semestru se budeme setkávat se zadáními, která budete řešit společně v těchto týmech, aby se podpořila vzájemná spolupráce a sdílení zkušeností.
* **Pro studenty Informatiky 1 (Úvodní hodina):** Na první hodině proběhne **úvodní písemný test**. Jde o krátký úkol zaměřený na ověření vašeho algoritmického myšlení. Jelikož jste v předchozím semestru absolvovali výuku v jazyce C, můžete k řešení využít jeho syntaxi, jakýkoliv jiný jazyk, který ovládáte, nebo zvolit volnou formu (pseudokód). Cílem je zjištění úrovně algoritmického myšlení studentů, které ještě osobně neznám.
* **Příprava na příští hodinu:** Podíváme se na základní syntaxi, proměnné, datové typy a první jednoduché programy.
