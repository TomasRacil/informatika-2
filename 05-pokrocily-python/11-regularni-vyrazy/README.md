# **11 - Regulární výrazy (Regular Expressions)**

Regulární výrazy (zkráceně **RegEx** nebo **re**) jsou extrémně silný nástroj pro práci s textem. Jde o speciální jazyk, kterým definujete **vzor (pattern)**, a počítač pak hledá text, který tomuto vzoru odpovídá.

Místo psaní desítek podmínek typu `if "a" in text or "b" in text` napíšete jeden regex. Používají se pro:

* **Validaci** (je to platný e-mail? telefon?).  
* **Vyhledávání** (najdi všechny IP adresy v logu).  
* **Nahrazování** (změň formát data z YYYY-MM-DD na DD.MM.YYYY).  
* **Parsování** (vytažení konkrétních hodnot z textu).

V Pythonu pro práci s nimi používáme vestavěný modul `import re`.

## **Užitečné nástroje**

Než začnete psát regexy do kódu, je lepší si je vyzkoušet nanečisto.  
Doporučujeme stránku [regex101.com](https://regex101.com/).

1. Vlevo v menu vyberte **Python**.  
2. Do horního pole pište svůj regex.  
3. Do dolního pole vložte testovací text.  
4. Vpravo uvidíte vysvětlení ("Explanation"), co přesně váš vzor dělá.

## **Základní syntaxe**

V Pythonu píšeme regexy jako tzv. **raw stringy** s předponou `r` (např. `r"d+"`). To proto, aby Python neinterpretoval zpětná lomítka jako speciální znaky (např. `\n` jako nový řádek), ale poslal je přímo regex enginu.

### **1. Metaznaky (Znaky se speciálním významem)**

| Znak | Význam | Příklad |
| :---- | :---- | :---- |
| `.` | Jakýkoliv znak (kromě nového řádku) | `a.c` najde "abc", "adc", "a@c" |
| `^` | Začátek řetězce (nebo řádku) | `^Ahoj` najde "Ahoj" jen na začátku textu |
| `$` | Konec řetězce (nebo řádku) | `konec$` najde "konec" jen na konci textu |
| `\` | Ruší speciální význam znaku (escape) | `\.` hledá skutečnou tečku |
| `\|`  | Logické NEBO (OR) | `a\|b` najde `a` nebo `b`|
| `[]` | Množina znaků (jeden z nich) | `[aeiou]` najde samohlásku |
| `[^]` | Negace množiny (žádný z nich) | `[^0-9]` najde cokoliv, co není číslo |
| `()` | Skupina (pro logické spojení nebo extrakci) | `(abc)+` hledá "abc", "abcabc"... |

### **2. Kvantifikátory (Opakování)**

Určují, kolikrát se má předchozí znak (nebo skupina) opakovat.

| Znak | Počet opakování | Příklad | Shoda |
| :---- | :---- | :---- | :---- |
| `*` | 0 nebo více | `Haf*` | "Ha", "Haf", "Hafff" |
| `+` | 1 nebo více | `Haf+` | "Haf", "Hafff" (ne "Ha") |
| `?` | 0 nebo 1 (volitelné) | `Colou?r` | "Color", "Colour" |
| `{n}` | Přesně n-krát | `d{3}` | "123", "999" |
| `{n,m}` | Od n do m krát | `d{2,4}` | "12", "123", "1234" |

### **3. Speciální sekvence (Zkratky)**

| Zkratka | Význam | Ekvivalent |
| :---- | :---- | :---- |
| `\d` | Číslice (Digit) | `[0-9]` |
| `\D` | Cokoliv kromě číslice | `[^0-9]` |
| `\w` | Znak slova (Word char: a-z, 0-9, _) | `[a-zA-Z0-9_]` |
| `\W` | Ne-znakový symbol (mezery, tečky...) | `[^a-zA-Z0-9_]` |
| `\s` | Bílý znak (Space: mezera, tabulátor) | `[ \t\n\r\f\v]` |
| `\S` | Nebílý znak | `[^ \t\n\r\f\v]` |

## **Hlavní funkce modulu `re`**

### **`re.search(vzor, text)`**

Prohledá **celý** text a vrátí první shodu jako objekt `Match`. Pokud nenajde nic, vrátí `None`.

```python
if re.search(r"pes", "Mám doma psa."):  
    print("Nalezeno!")
```

### **`re.match(vzor, text)`**

Hledá shodu **pouze na úplném začátku** textu.

```python
re.match(r"pes", "Mám doma psa") # Vrátí None (pes není na začátku)
```

### **`re.findall(vzor, text)`**

Vrátí **seznam** všech nalezených výskytů (jako řetězce). Nejpoužívanější funkce pro dolování dat.

```python
text = "Tel: 123 456, Fax: 789 000"  
cisla = re.findall(r"d{3}", text)   
# Výsledek: ['123', '456', '789', '000']
```

### **`re.sub(vzor, nahrada, text)`**

Nahradí nalezené vzory jiným textem (Search & Replace).

```python
# Odstranění přebytečných mezer  
cisty = re.sub(r"s+", " ", "Text   s   mezerami")  
# Výsledek: "Text s mezerami"
```

### **`re.split(vzor, text)`**

Rozdělí text podle vzoru (silnější než `str.split()`, protože umí dělit podle více oddělovačů).

## **Pokročilé koncepty**

### **Skupiny (Groups)**

Pomocí závorek `()` můžeme z textu "vyzobnout" jen konkrétní část.

```python
vzor = r"Cena: (d+) Kč"  
text = "Cena: 500 Kč"  
shoda = re.search(vzor, text)  
print(shoda.group(1)) # Vypíše: 500 (obsah první závorky)
```

### **Vlajky (Flags)**

Mění chování regexu. Předávají se jako poslední parametr.

* `re.IGNORECASE` (`re.I`): Nerozlišuje velká/malá písmena.  
* `re.DOTALL` (`re.S`)`: Tečka `.` bude brát i nový řádek `\n`.  
* `re.MULTILINE` (`re.M`): `^` a `$` fungují pro každý řádek textu, ne jen pro celý řetězec.

```python
re.search(r"ahoj", "AHOJ světe", re.IGNORECASE) # Najde shodu  
```
---
## **Cvičení**

### **1. Hledání dat**
Máte text: `"Termíny jsou 12.01.2023, 5.5.2023 a také 31.12.2023."`
Pomocí `re.findall` najděte všechna data. Zkuste vzor, který zachytí formát DD.MM.YYYY (nápověda: `\d{1,2}\.` ...).

### **2. Validace e-mailu**
Napište regex pro jednoduchou validaci e-mailu (stačí zkontrolovat, že obsahuje zavináč a tečku v doméně). Otestujte ho na řetězcích `"jan@novak.cz"` (projde) a `"jan.novak.cz"` (neprojde).

### **3. Cenzura**
Máte větu: `"Tajné heslo je tajne123."`
Pomocí `re.sub` nahraďte všechna čísla znakem `X`. Výsledek: `"Tajné heslo je tajneXXX."`
