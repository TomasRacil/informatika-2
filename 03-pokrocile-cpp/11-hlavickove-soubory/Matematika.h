#pragma once
/*
TOTO JE HLAVIČKOVÝ SOUBOR (HEADER FILE) - Matematika.h
Obsahuje pouze DEKLARACE (co funkce dělají), nikoli jejich implementaci (jak to dělají).
Slouží jako "rozhraní" nebo "veřejná nabídka" toho, co tento modul umí.
*/

// Include guard - brání vícenásobnému vložení souboru
#ifndef MATEMATIKA_H
#define MATEMATIKA_H

#include <string> // Hlavičkové soubory mohou includovat jiné hlavičkové soubory

// --- Deklarace funkcí (prototypy) ---
// Říkáme kompilátoru: "Někde existuje funkce 'secti',
// která bere dva inty a vrací int."
int secti(int a, int b);

double secti(double a, double b); // Přetížená verze

// --- Definice třídy ---
// Definice třídy (její struktura, jaké má členy a metody) 
// patří do hlavičkového souboru.
class Kalkulacka
{
private:
    int pocetOperaci;

public:
    // Konstruktor (deklarace)
    Kalkulacka();

    // Metoda (deklarace)
    int vynasob(int a, int b);

    // Metoda (deklarace)
    int getPocetOperaci();
};


#endif // MATEMATIKA_H

