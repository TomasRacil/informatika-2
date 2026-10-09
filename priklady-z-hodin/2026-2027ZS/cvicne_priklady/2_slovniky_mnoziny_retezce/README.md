### Úkol 2: Slovníky, množiny a textové řetězce
Napište funkci `analyzuj_frekvenci_slov(text, ignorovana_slova)`.

**Požadavky:**

* Očistěte vstupní text: převeďte ho na malá písmena a odstraňte znaky `,`, `.`, `!`, `?`.
* Spočítejte výskyty slov pomocí slovníku (`dict`).
* Slova obsažená v množině `ignorovana_slova` přeskočte.
* Pomocí operací nad množinami (`set`) sestavte množinu všech slov, která se v textu vyskytla **právě jednou**.
* Funkce vrátí slovník frekvencí a množinu unikátních slov.

**Testovací kód:**

```python
vstup = "Python je skvělý, ale skriptovací jazyk je rychlý. Python má přehlednou syntaxi."
stop_slova = {"je", "ale", "má"}

frekvence, unikatni = analyzuj_frekvenci_slov(vstup, stop_slova)
print("Frekvence:", frekvence)
print("Pouze jednou:", unikatni)

```