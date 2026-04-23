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
| 02 | [Reference vs Ukazatele](./02-reference-vs-ukazatele/) | Co je to reference, jak se liší od ukazatele, pass-by-reference a kdy co použít. |
| 03 | [Dynamická alokace paměti](./03-dynamicka-alokace-pameti/) | Stack vs. Heap, operátory `new` a `delete`/`delete[]`, alokace polí, úniky paměti (memory leaks). |
| 04 | [Ukazatele a funkce](./04-ukazatele-a-funkce/) | Rozdíl pass-by-value vs. pass-by-pointer, předávání polí (array decay), návrat ukazatele z funkce (včetně rizik). |
| 05 | [Dynamické datové struktury](./05-dynamicke-datove-sturktury/) | Úvod do spojových seznamů (implementace uzlu, vkládání, mazání, procházení). |
| 06 | [Úvod do OOP](./06-uvod-do-oop/) | Principy (zapouzdření, dědičnost, polymorfismus), třídy a objekty. |
| 07 | [Konstruktory a destruktory](./07-konstruktory-a-destruktory/) | Role konstruktoru, typy (defaultní, parametrický), přetěžování, destruktor. |
| 08 | [Dědičnost](./08-dedicnost/) | Odvozené třídy, překrývání metod, viditelnost (public, private, protected). |
| 09 | [Polymorfismus](./09-polymorfismus/) | Virtuální metody, abstraktní třídy, dynamické vázání. |
| 10 | [Přetěžování operátorů](./10-pretezovani-operatoru/) | Přetížení aritmetických, relačních a dalších operátorů pro vlastní třídy. |
| 11 | [Hlavičkové soubory](./11-hlavickove-soubory/)|Rozdělení kód ud dílčích celků (hlavičkových a zdrojových souborů)|
| 12 | [Šablony (Templates)](./12-sablony/) | Funkční šablony, třídní šablony, obecné programování. |
| 13 | [Statické členy](./13-staticke-cleny/) | Statické atributy a metody, jejich využití. |
| 14 | [Úvod do STL](./14-uvod-do-stl/) | Základní kontejnery (`vector`, `list`, `map`), iterátory a algoritmy. |
| 15 | [Smart pointers](./15-smart-pointers/) | Moderní a bezpečná alternativa k ukazatelům. |
| 16 | [Lambda a algoritmy](./16-lambda-a-algoritmy/) | Představení konceptu lambda funkce a jejího využití. |
| 17 | [Regulární výrazy](./17-regularni-vyrazy/) | Úvod do regulárních výrazů v C++. | 
| 18 | [Argumenty příkazové řádky](./18-argumenty-prikazove-radky/) | Předávání parametrů programu při spuštění. |
| 19 | [Vlákna a paralelizmus](./19-vlakna-a-paralelni-programovani/) | Práce s vlákny, mutexy a atomickými operacemi. |
| 20 | [Sdílená paměť](./20-sdilena-pamet/) | Komunikace mezi procesy pomocí sdílené paměti. |
| 21 | [Síťová komunikace](./21-sitova-komunikace/) | Berkeley Sockets, TCP a UDP. |
| 22 | [Asynchronní programování](./22-asynchronni-programovani/) | Úlohy (`std::async`, `std::future`) a C++20 korutiny. |