### Téma 15: Regulární výrazy v C++ (`<regex>`)

Regulární výraz (často zkracováno na "regex") je sekvence znaků, která definuje **vyhledávací vzor** (pattern). Je to extrémně mocný nástroj pro prohledávání, validaci, extrakci a nahrazování textu.

Pokud potřebujete ověřit, zda má e-mail správný formát, najít všechna telefonní čísla v textu nebo extrahovat data ze strukturovaného logu, regulární výrazy jsou tím správným nástrojem.

V C++ (od standardu C++11) je podpora regulárních výrazů dostupná přes hlavičkový soubor `<regex>`.

### Základní syntaxe Regexu

C++ `std::regex` standardně používá syntaxi **ECMAScript** (stejnou jako JavaScript nebo Python). Zde jsou nejdůležitější metaznaky:

| Symbol | Popis | Příklad |
| :--- | :--- | :--- |
| `.` | Jakýkoli jeden znak (kromě nového řádku) | `h.t` odpovídá "hot", "hat", "h_t" |
| `*` | 0 nebo více výskytů předchozího znaku/skupiny | `a*` odpovídá "", "a", "aa" |
| `+` | 1 nebo více výskytů předchozího znaku/skupiny | `a+` odpovídá "a", "aa", ale ne "" |
| `?` | 0 nebo 1 výskyt předchozího znaku/skupiny | `colou?r` odpovídá "color" i "colour" |
| `{n}` | Přesně `n` opakování. | `\d{3}` odpovídá "123", ale ne "12" |
| `{n,}` | Nejméně `n` opakování. | `\d{2,}` odpovídá "12", "123", "1234" |
| `{n,m}`| Nejméně `n`, nejvíce `m` opakování. | `\w{2,5}` odpovídá 2 až 5 písmenům/číslům |
| `\d` | Jakákoli číslice (0-9). | |
| `\D` | Jakýkoli znak, který **není** číslice. | |
| `\s` | Jakýkoli "bílý znak" (mezera, tabulátor, `\n`) | `Hello\sWorld` |
| `\S` | Jakýkoli znak, který **není** bílý znak. | |
| `\w` | Jakýkoli "slovní" znak (písmeno, číslo, podtržítko) | `\w+` odpovídá "word_123" |
| `\W` | Jakýkoli znak, který **není** "slovní". | |
| `[]` | Sada znaků. Shoduje se s jedním znakem ze sady. | `[aeiou]` odpovídá jakékoli samohlásce |
| `[^]` | Negovaná sada. Shoduje se s jedním znakem, který není v sadě. | `[^0-9]` odpovídá všemu, co není číslice |
| `( )` | **Zachytávací skupina (Capturing Group).** Uloží část shody pro pozdější použití. | `(ahoj)` |
| `\|` | Logické NEBO (OR). | `(com\|org\|net)` |
| `^` | Začátek řetězce. | `^Start` (musí začínat na "Start") |
| `$` | Konec řetězce. | `end$` (musí končit na "end") |

#### Důležitá poznámka pro C++: Zpětná lomítka!

Protože zpětné lomítko (`\`) je v C++ řetězcích samo o sobě *escape* znak (např. `\n` je nový řádek), musíte ho **vždy zdvojit**, pokud chcete, aby bylo součástí regulárního výrazu.

  * Regex pro číslici `\d` se v C++ stringu zapíše jako `"\\d"`.
  * Regex pro cestu `C:\Temp` se zapíše jako `"C:\\\\Temp"`.
  * Regex pro `(com|org)` se zapíše jako `"(com\\|org)"`.

##### Raw stringy (C++11)

C++11 zavedlo **raw stringy**, které řeší problém se zpětnými lomítky. Raw string se zapisuje jako `R"(obsah)"`. V raw stringu se zpětná lomítka interpretují doslova, bez escapování:

  * Místo `"\\d"` stačí napsat `R"(\d)"`
  * Místo `"C:\\\\Temp"` stačí napsat `R"(C:\Temp)"`
  * Místo `"(com\\|org)"` stačí napsat `R"((com|org))"`

Příklad:
```cpp
// Bez raw stringu - obtížné na čtení
std::regex vzor1("\\d{3}-\\d{3}-\\d{3}");

// S raw stringem - jasněji viditelný regex
std::regex vzor2(R"(\d{3}-\d{3}-\d{3})");
```

Oba způsoby jsou funkčně ekvivalentní, ale raw stringy jsou **čitelnější** a méně náchylné k chybám. Pokud máte ve stringu výraz `)"`, můžete změnit separator: `R"delim(obsah)delim"`.

```cpp
// Raw string s vlastním separátorem (máme )" v obsahu)
std::regex vzor(R"delim(pattern)"here)delim");
```


### Klíčové komponenty v `<regex>`

Pro práci s regexy v C++ používáme tři hlavní funkce a dva hlavní objekty.

  * **Objekty:**

    1.  `std::regex`: Objekt, který drží zkompilovaný regulární výraz. Vytvoření tohoto objektu je náročnější operace, proto pokud vzor používáte opakovaně, vytvořte jej jen jednou.
    2.  `std::smatch`: Objekt (kontejner), který uchovává výsledky vyhledávání. `smatch` je zkratka pro "string match". Je to v podstatě pole `std::ssub_match` objektů (které se chovají jako stringy).

  * **Funkce:**

    1.  **`std::regex_match(text, vzor)`**: Vrací `true`, pouze pokud se **CELÝ** řetězec `text` shoduje se vzorem `vzor`. Ideální pro validaci (např. "Je toto platné rodné číslo?").
    2.  **`std::regex_search(text, shody, vzor)`**: Vrací `true`, pokud se **alespoň ČÁST** řetězce `text` shoduje se vzorem `vzor`. Pokud je `true`, naplní objekt `shody` (typu `smatch`) nalezenými podřetězci. Ideální pro hledání a extrakci dat.
    3.  **`std::regex_replace(text, vzor, format)`**: Nahradí všechny výskyty, které odpovídají `vzor` v `text`u, za řetězec `format`.


### Ukázky použití

Příklady použití `regex_search`, `regex_match` a `regex_replace` najdete v souboru `main.cpp`.

#### 1. Validace (`regex_match`)

Používá se, když chcete ověřit, že *celý* vstup odpovídá formátu.

```cpp
std::string email = "jmeno.prijmeni@email.cz";
std::regex email_vzor(R"([\w.-]+@[\w.-]+\.[a-zA-Z]{2,})");

if (std::regex_match(email, email_vzor)) {
    std::cout << "Email je platny." << std::endl;
}
```

#### 2. Hledání a extrakce (`regex_search` a `smatch`)

Používá se k nalezení části textu a "vytažení" konkrétních informací pomocí skupin `( )`.

```cpp
std::string text = "ID: 42, Jmeno: Jan Novak";
std::regex vzor(R"(ID: (\d+), Jmeno: (\w+) (\w+))");
std::smatch shody;

if (std::regex_search(text, shody, vzor)) {
    // shody[0] je vždy celý nalezený řetězec: "ID: 42, Jmeno: Jan Novak"
    // shody[1] je první skupina (\d+): "42"
    // shody[2] je druhá skupina (\w+): "Jan"
    // shody[3] je třetí skupina (\w+): "Novak"
    
    std::string id_str = shody[1].str();
    std::string jmeno = shody[2].str();
    std::string prijmeni = shody[3].str();
    
    std::cout << "Nalezeno: " << jmeno << " " << prijmeni << " (ID: " << id_str << ")" << std::endl;
}
```

#### 3. Nahrazování (`regex_replace`)

Používá se k nalezení všech shod a jejich nahrazení.

```cpp
std::string text = "Telefon je 123-456-789. Volejte 987-654-321.";
std::regex vzor_telefon(R"(\d{3}-\d{3}-\d{3})");
std::string format = "[REDACTED]";

std::string vysledek = std::regex_replace(text, vzor_telefon, format);
// vysledek: "Telefon je [REDACTED]. Volejte [REDACTED]."
```

#### 4. Iterace (nalezení všech shod)

`regex_search` najde jen první shodu. Pro nalezení všech musíme použít cyklus a prohledávat zbytek řetězce.

```cpp
std::string vstup = "Barvy: red, green, blue";
std::regex vzor_barva(R"((\w+))"); // Najde všechna slova
std::smatch shody;
std::string::const_iterator startHledani(vstup.cbegin());

while (std::regex_search(startHledani, vstup.cend(), shody, vzor_barva))
{
    std::cout << "Nalezena barva: " << shody[1].str() << std::endl;
    startHledani = shody[0].second; // Posun začátek hledání na konec poslední shody
}
// Vypíše: Barvy, red, green, blue
```
---
## **Cvičení**

### **1. Čas ve formátu HH:MM**
Napište regulární výraz, který ověří, zda je řetězec platným časem (00:00 až 23:59). Pozor na neplatné časy jako 25:99.

### **2. Hashtagy**
V extrahujte z textu všechny hashtagy (slova začínající znakem `#`).
Text: "Dnes je krásně #slunce #pohoda #programovani"

### **3. Cenzura**
Nahraďte v textu všechna telefonní čísla (ve formátu 9 čísel) řetězcem "[SKRYTO]".
