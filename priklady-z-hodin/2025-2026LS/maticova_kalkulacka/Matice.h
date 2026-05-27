#pragma once

#include <cstdlib>
#include <iostream>


template<typename T>
class Matice
{
private:
    T **matice;
    int radky;
    int sloupce;

public:
    Matice(int radky, int sloupce);
    Matice(int radky, int sloupce, T inicializacni_hodnota);
    Matice(const Matice &other);
    ~Matice();

    void vypis_matici();
    Matice secti_matice(const Matice &matice_2);
    Matice operator+(const Matice &matice_2);
    Matice nasob_matice(const Matice &matice_2);
    Matice transponuj_matici();
    Matice skalarni_nasobeni(T scalar);
    T determinant_matice();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matice<U>& m);
};

#include "Matice.cpp"