### Úkol 3: Funkce, mutabilita a kopírování dat

Implementujte dvě funkce pro správu uživatelských profilů:

1. `pridej_opravneni(profil, opravneni, role=None)`:
    * Pokud `role` není zadána, nastaví se jako prázdný seznam `[]` (ošetřete správně výchozí hodnotu v signatuře funkce).
    * Přidá `opravneni` do seznamu `role` a vrátí aktualizovaný slovník.


2. `klonuj_a_uprav_profil(puvodni_profil, nova_data)`:
    * Vytvoří nezávislou kopii slovníku `puvodni_profil` (včetně vnořených seznamů).
    * Aplikuje změny z `nova_data` pouze na novou kopii tak, aby původní slovník zůstal beze změny.



**Testovací kód:**

```python
p1 = {"jmeno": "Jan", "prava": ["read"]}
p2 = pridej_opravneni(p1, "write")

kopie = klonuj_a_uprav_profil(p1, {"jmeno": "Petr", "prava": ["admin"]})
print("Původní:", p1)
print("Kopie:", kopie)

```