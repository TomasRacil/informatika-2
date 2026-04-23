/*
TOTO JE HLAVNÍ SOUBOR (main.cpp)
Tento soubor "používá" kód definovaný v Matematika.h a Matematika.cpp.
*/

#include <iostream>

// Includujeme POUZE hlavičkový soubor.
// O propojení s Matematika.cpp se postará linker při kompilaci.
#include "Matematika.h" 

// NIKDY neincludujte .cpp soubor!
// #include "Matematika.cpp" // <-- TOTO JE ŠPATNĚ! Způsobilo by chybu "multiple definition".

int main()
{
    std::cout << "--- Testovani funkci ---" << std::endl;
    
    // Voláme funkce, jejichž kód je v Matematika.cpp
    // Kompilátor ví, že existují, díky #include "Matematika.h"
    std::cout << "secti(5, 3) = " << secti(5, 3) << std::endl;
    std::cout << "secti(2.5, 4.1) = " << secti(2.5, 4.1) << std::endl;

    std::cout << "\n--- Testovani tridy Kalkulacka ---" << std::endl;

    // Vytvoříme instanci třídy
    // Automaticky se volá konstruktor z Matematika.cpp
    Kalkulacka calc; 

    // Voláme metody třídy
    int vysledek = calc.vynasob(6, 7);
    std::cout << "Vysledek nasobeni: " << vysledek << std::endl;
    std::cout << "Pocet operaci: " << calc.getPocetOperaci() << std::endl;

    calc.vynasob(2, 3);
    std::cout << "Pocet operaci: " << calc.getPocetOperaci() << std::endl;

    return 0;
}

/*
JAK TO ZKOMPILOVAT?

Protože se projekt skládá z více souborů (.cpp), nemůžeme použít 
jednoduché "Run Code" nebo "Play" tlačítko, které by zkompilovalo 
pouze aktivní soubor (main.cpp).

Musíme kompilátoru říct, aby spojil VŠECHNY potřebné .cpp soubory.

Ve VS Code:
1.  Otevřete paletu příkazů (Ctrl+Shift+P nebo Cmd+Shift+P).
2.  Napište "Tasks: Run Build Task" (nebo "Spustit úlohu sestavení").
3.  Vyberte úlohu "C/C++: g++ build active folder" (nebo "C/C++: g++ sestavit aktivní složku").

Tato úloha (definovaná v .vscode/tasks.json) řekne kompilátoru, aby vzal
všechny soubory končící na .cpp v aktuálním adresáři (main.cpp i Matematika.cpp),
zkompiloval je a slinkoval dohromady do jednoho spustitelného souboru.

Alternativně v terminálu:
g++ main.cpp Matematika.cpp -o program
./program
*/

