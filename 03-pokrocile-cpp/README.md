# 03 - Pokročilé C++

Tato sekce se věnuje pokročilým konceptům jazyka C++. Poté, co jsme v sekci [02 - Základy C++](../02-zaklady-cpp/README.md) zvládli syntaxi, proměnné, podmínky, cykly a funkce, se nyní ponoříme hlouběji do témat, která dělají C++ tak silným (a někdy i složitým) jazykem.

Zaměříme se na dvě klíčové oblasti:
1.  **Přímá správa paměti:** Naučíme se pracovat s ukazateli a dynamicky alokovat paměť. To nám umožní vytvářet efektivní a flexibilní datové struktury.
2.  **Objektově orientované programování (OOP):** Osvojíme si principy zapouzdření, dědičnosti a polymorfismu pro návrh modulárních a znovupoužitelných aplikací.

Nakonec se podíváme na moderní prvky C++, jako jsou šablony, výjimky a standardní knihovna (STL).

## Témata

| Pořadí | Téma | Popis |
| :--- | :--- | :--- |
| 01 | [Úvod do ukazatelů](./01-uvod-do-ukazatelu/) | Co je ukazatel, operátor adresy (`&`) a dereference (`*`), ukazatele a pole. |
| 02 | [Dynamická alokace paměti](./02-dynamicka-alokace-pameti/) | Stack vs. Heap, operátory `new` a `delete`/`delete[]`, alokace polí, úniky paměti (memory leaks). |
| 03 | [Ukazatele a funkce](./03-ukazatele-a-funkce/) | Rozdíl pass-by-value vs. pass-by-pointer, předávání polí (array decay), návrat ukazatele z funkce (včetně rizik). |
| 04 | [Dynamické datové struktury](./04-dynamicke-datove-sturktury/) | Úvod do spojových seznamů (implementace uzlu, vkládání, mazání, procházení). |
| 05 | [Úvod do OOP](./05-uvod-do-oop/) | Principy (zapouzdření, dědičnost, polymorfismus), třídy a objekty. |
| 06 | [Konstruktory a destruktory](./06-konstruktory-a-destruktory/) | Role konstruktoru, typy (defaultní, parametrický), přetěžování, destruktor. |
| 07 | [Dědičnost](./07-dedicnost/) | Odvozené třídy, překrývání metod, viditelnost (public, private, protected). |
| 08 | [Polymorfismus](./08-polymorfismus/) | Virtuální metody, abstraktní třídy, dynamické vázání. |
| 09 | [Přetěžování operátorů](./09-pretezovani-operatoru/) | Přetížení aritmetických, relačních a dalších operátorů pro vlastní třídy. |
| 10 | [Hlavičkové soubory](./10-hlavickove-soubory/)|Rozdělení kód ud dílčích celků (hlavičkových a zdrojových souborů)|
| 11 | [Šablony (Templates)](./11-sablony/) | Funkční šablony, třídní šablony, obecné programování. |
| 12 | [Statické členy](./12-staticke-cleny/) | Statické atributy a metody, jejich využití. |
| 13 | [Úvod do STL](./13-uvod-do-stl/) | Základní kontejnery (`vector`, `list`, `map`), iterátory a algoritmy. |
| 14 | [Smart pointers](./14-smart-pointers/) | Moderní a bezpečná alternativa k ukazatelům. |
| 15 | [Lambda a algoritmy](./15-lambda-a-algoritmy/) | Představení konceptu lambda funkce a jejího využití. |
| 16 | [Regulární výrazy](./16-regularni-vyrazy/) | Úvod do regulárních výrazů v C++. | 
| 17 | [Argumenty příkazové řádky](./17-argumenty-prikazove-radky/) | Předávání parametrů programu při spuštění. |
| 18 | [Vlákna a paralelizmus](./18-vlakna-a-paralenni-programovani/) | Práce s vlákny, mutexy a atomickými operacemi. |
| 19 | [Sdílená paměť](./19-sdilena-pamet/) | Komunikace mezi procesy pomocí sdílené paměti. |
| 20 | [Síťová komunikace](./20-sitova-komunikace/) | Berkeley Sockets, TCP a UDP. |
| 21 | [Asynchronní programování](./21-asynchronni-programovani/) | Úlohy (`std::async`, `std::future`) a C++20 korutiny. |