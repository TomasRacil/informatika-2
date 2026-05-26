#include "Matice.h"

#include <iostream>
#include <stdexcept>

Matice::Matice(int radky, int sloupce, int inicializacni_hodnota)
{
    this->radky = radky;
    this->sloupce = sloupce;

    matice = new int *[radky];
    for (int i = 0; i < radky; ++i)
    {
        matice[i] = new int[sloupce];
        for (int j = 0; j < sloupce; j++)
        {
            if (inicializacni_hodnota == NULL)
            {
                matice[i][j] = rand() % 10;
            }
            else
            {
                matice[i][j] = inicializacni_hodnota;
            }
        }
    }
}

Matice::Matice(const Matice &other)
{
    this->radky = other.radky;
    this->sloupce = other.sloupce;
    this->matice = new int *[radky];
    for (int i = 0; i < radky; i++)
    {
        this->matice[i] = new int[sloupce];
        for (int j = 0; j < sloupce; j++)
        {
            this->matice[i][j] = other.matice[i][j];
        }
    }
}

void Matice::vypis_matici()
{
    std::cout << "Matice:" << std::endl;
    if (matice == nullptr)
    {
        std::cout << "Matice je prazdna." << std::endl;
        return;
    }
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            std::cout << matice[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matice Matice::secti_matice(const Matice &matice_2)
{
    if (radky != matice_2.radky || sloupce != matice_2.sloupce)
    {
        throw std::runtime_error("Matice nejsou stejne velke.");
    }
    Matice vysledek(radky, sloupce);
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek.matice[i][j] = matice[i][j] + matice_2.matice[i][j];
        }
    }
    return vysledek;
}

Matice Matice::operator+(const Matice &matice_2)
{
    if (radky != matice_2.radky || sloupce != matice_2.sloupce)
    {
        throw std::runtime_error("Matice nejsou stejne velke.");
    }
    Matice vysledek(radky, sloupce);
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek.matice[i][j] = matice[i][j] + matice_2.matice[i][j];
        }
    }
    return vysledek;
}

Matice Matice::nasob_matice(const Matice &matice_2)
{
    if (sloupce != matice_2.radky)
    {
        throw std::runtime_error("Matice nejsou kompatibilni pro nasobeni.");
    }
    Matice vysledek = Matice(radky, matice_2.sloupce, 0);
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < matice_2.sloupce; j++)
        {
            for (int k = 0; k < sloupce; k++)
            {
                vysledek.matice[i][j] +=
                    (matice[i][k] * matice_2.matice[k][j]);
            }
        }
    }
    return vysledek;
}

Matice Matice::transponuj_matici()
{
    Matice vysledek = Matice(sloupce, radky, 0);
    for (int i = 0; i < sloupce; i++)
    {
        for (int j = 0; j < radky; j++)
        {
            vysledek.matice[i][j] = matice[j][i];
        }
    }
    return vysledek;
}

Matice Matice::skalarni_nasobeni(int scalar)
{
    Matice vysledek = Matice(radky, sloupce, 0);
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek.matice[i][j] = matice[i][j] * scalar;
        }
    }
    return vysledek;
}

int Matice::determinant_matice()
{
    int vysledek = 0;
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek += matice[i][j];
        }
    }
    return vysledek;
}

Matice::~Matice()
{
    for (int i = 0; i < radky; ++i)
    {
        delete[] matice[i];
        matice[i] = nullptr;
    }
    delete[] matice;
    matice = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Matice &m)
{
    os << "Matice:" << std::endl;
    for (int i = 0; i < m.radky; i++)
    {
        for (int j = 0; j < m.sloupce; j++)
        {
            os << m.matice[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}
