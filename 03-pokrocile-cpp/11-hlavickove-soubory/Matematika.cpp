/*
TOTO JE IMPLEMENTAČNÍ SOUBOR (SOURCE FILE) - Matematika.cpp
Obsahuje DEFINICE (těla) funkcí a metod, které byly
deklarovány v souboru Matematika.h.
*/

// 1. Vždy includujeme odpovídající hlavičkový soubor
#include "Matematika.h"

// Includujeme další knihovny, které potřebujeme POUZE pro implementaci
// (main.cpp je nemusí vidět)
#include <iostream> 

// --- Definice (implementace) funkcí ---

int secti(int a, int b)
{
    // Toto je tělo funkce (definice)
    return a + b;
}

double secti(double a, double b)
{
    // Tělo přetížené funkce
    return a + b;
}


// --- Definice (implementace) metod třídy ---

// Pomocí 'Kalkulacka::' říkáme, že definujeme metody patřící do třídy Kalkulacka

Kalkulacka::Kalkulacka()
{
    pocetOperaci = 0; // Inicializujeme atribut v konstruktoru
    std::cout << "Vytvarim kalkulacku..." << std::endl;
}

int Kalkulacka::vynasob(int a, int b)
{
    pocetOperaci++; // Můžeme přistupovat k privátním členům
    return a * b;
}

int Kalkulacka::getPocetOperaci()
{
    return pocetOperaci;
}

