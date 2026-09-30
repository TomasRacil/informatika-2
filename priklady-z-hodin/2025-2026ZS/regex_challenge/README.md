# **ZADÁNÍ: OPERACE HAYSTACK – FORENZNÍ ANALÝZA DAT**


## **KONTEXT**

Zpravodajská divize zachytila fragmentovaný datový dump. Soubor `dump_final.txt` obsahuje surová data. Vaším úkolem je provést forenzní extrakci klíčových identifikátorů a sestavit **Master Key**.

## **CÍLE MISE**

Váš tým má 60 minut na analýzu souboru a sestavení Master Key.  
Musíte pochopit strukturu dat, identifikovat vzory a extrahovat informace.

## **PROTOKOL (PRAVIDLA)**

1. **Nástroje:** Python (moduly `re`, `base64`, `statistics`, `datetime`).  
2. **Metodika:** Řešení musí být algoritmická.
3. **Spolupráce:** Rozdělte si moduly. Čas běží.

## **OBLASTI ANALÝZY (MODULY)**

### **MODUL 1: KOMUNIKAČNÍ KANÁLY**

Subjekty používají různé e-mailové služby. Některé adresy jsou záměrně "zašuměné" náhodnými znaky, aby zmátly automatické skenery.

* **Analýza:** Prozkoumejte formát e-mailů v logu. Zjistěte, jakým způsobem je do uživatelského jména vkládán šum, a odstraňte ho.  
* **Filtr:** Ignorujte veškerou komunikaci, která pochází z interního testovacího prostředí (identifikujte doménu používanou pro testy).  
* **Cíl pro klíč:** Počet unikátních, očištěných e-mailových adres, jejichž uživatelská část (před `@`) má délku přesně 8 znaků.

### **MODUL 2: KRYPTO-TRANSAKCE**

Log obsahuje záznamy o transakcích v kryptoměnách.

* **Analýza:** Identifikujte formát hashů transakcí. **Hint:** Hledejte řetězce začínající prefixem `0x`, následované delší sekvencí hexadecimálních znaků (0-9, a-f), reprezentující hodnotu o velikosti 64 až 256 bitů.
* **Cíl:** Zajímají nás pouze ty transakce, které byly systémem **úspěšně potvrzeny**. Najděte způsob, jak v logu spolehlivě odlišit potvrzené transakce od ostatních.  
* **Cíl pro klíč:** Sečtěte všechny číslice (0-9), které se vyskytují v **posledním** nalezeném validním (potvrzeném) hashi v souboru.

### **MODUL 3: ČASOVÁ OS**

Data v logu jsou v různých formátech.

* **Analýza:** Identifikujte používané formáty datumu.  
* **Filtr:** Systém akceptuje pouze striktní standardy: ISO 8601 a český národní standard. Všechny ostatní formáty (americké, textové, atd.) považujte za poškozené záznamy a ignorujte je. Dále bereme v úvahu pouze události v rozmezí let 2020 až 2025 (včetně).
* **Cíl pro klíč:** Normalizujte validní data, seřaďte je a určete **medián**. Výsledné datum (ve formátu `YYYYMMDD`) použijte pro klíč.

### **MODUL 4: SÍŤOVÁ IDENTIFIKACE (MAC vs IPv6)**

V síťovém provozu se objevují hardwarové adresy (MAC).

* **Analýza:** Extrahujte MAC adresy.  
* **Filtr:** Víme, že útočníci nepoužívají hardware od výrobců, jejichž MAC adresy začínají bytem `FF`. Tyto ignorujte.  
* **Cíl pro klíč:** Najděte **poslední platnou** MAC adresu v souboru (která splňuje podmínky). Pro klíč použijte její **třetí byte** (dvouznakovou hex hodnotu).

### **MODUL 5: DEKÓDOVÁNÍ PAYLOADU**

V datech jsou ukryty binární instrukce kódované v Base64.

* **Analýza:** Najděte kódované bloky dat. Po dekódování v nich hledejte řídící signály (číselné hodnoty spojené s příkazem pro spuštění).  
* **Cíl pro klíč:** Součet všech číselných hodnot těchto řídících signálů.

### **MODUL 6: DETEKCE ANOMÁLIÍ (PALINDROMY)**

Systém generuje chybové kódy ve formátu `ERR-<code>`.

* **Analýza:** Zajímají nás pouze ty kódy, které vykazují **symetrii** (jsou palindromy) a mají dostatečnou délku (alespoň 5 znaků).  
* **Cíl pro klíč:** Počet nalezených symetrických chyb.

## **MASTER KEY (HEX KONVERZE)**

Každý výsledek z modulu (M1-M6) převeďte do **hexadecimální soustavy**.

* Pokud je výsledkem číslo, převeďte ho na hex (např. `255` -> `FF`).  
* Pokud je výsledkem řetězec, který už je hex (např. část MAC adresy), nechte ho být.  
* Použijte **velká písmena**.  
* Výsledek vždy **doplňte na 4** znaky zleva nulami (např. `A1` -> `00A1`). Pokud je řetězec delší, použijte pouze **poslední 4 znaky**.

**Formát:** M1-M2-M3-M4-M5-M6