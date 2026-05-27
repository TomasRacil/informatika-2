#include "Matice.h"
#include <stdexcept>
#include <type_traits>

#ifndef MATICE_CPP
#define MATICE_CPP

template<typename T>
Matice<T>::Matice(int radky, int sloupce) : radky(radky), sloupce(sloupce)
{
    matice = new T *[radky];
    for (int i = 0; i < radky; ++i)
    {
        matice[i] = new T[sloupce];
        for (int j = 0; j < sloupce; j++)
        {
            if constexpr (std::is_integral_v<T>) {
                matice[i][j] = static_cast<T>(rand() % 10);
            } else if constexpr (std::is_floating_point_v<T>) {
                matice[i][j] = static_cast<T>(rand()% 100) / static_cast<T>(10);
            }
        }
    }
}

template<typename T>
Matice<T>::Matice(int radky, int sloupce, T inicializacni_hodnota) : radky(radky), sloupce(sloupce)
{
    matice = new T *[radky];
    for (int i = 0; i < radky; ++i)
    {
        matice[i] = new T[sloupce];
        for (int j = 0; j < sloupce; j++)
        {
            matice[i][j] = inicializacni_hodnota;
        }
    }
}

template<typename T>
Matice<T>::Matice(const Matice &other) : radky(other.radky), sloupce(other.sloupce)
{
    this->matice = new T *[radky];
    for (int i = 0; i < radky; i++)
    {
        this->matice[i] = new T[sloupce];
        for (int j = 0; j < sloupce; j++)
        {
            this->matice[i][j] = other.matice[i][j];
        }
    }
}

template<typename T>
void Matice<T>::vypis_matici()
{
    if (matice == nullptr)
    {
        std::cout << "Matice je prazdna." << std::endl;
        return;
    }
    std::cout << "Matice (" << radky << "x" << sloupce << "):" << std::endl;
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            std::cout << matice[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T>
Matice<T> Matice<T>::secti_matice(const Matice<T> &matice_2)
{
    if (radky != matice_2.radky || sloupce != matice_2.sloupce)
    {
        throw std::runtime_error("Matice nejsou stejne velke.");
    }
    Matice<T> vysledek(radky, sloupce, static_cast<T>(0));
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek.matice[i][j] = matice[i][j] + matice_2.matice[i][j];
        }
    }
    return vysledek;
}

template<typename T>
Matice<T> Matice<T>::operator+(const Matice<T> &matice_2)
{
    return secti_matice(matice_2);
}

template<typename T>
Matice<T> Matice<T>::nasob_matice(const Matice<T> &matice_2)
{
    if (sloupce != matice_2.radky)
    {
        throw std::runtime_error("Matice nejsou kompatibilni pro nasobeni.");
    }
    Matice<T> vysledek(radky, matice_2.sloupce, static_cast<T>(0));
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < matice_2.sloupce; j++)
        {
            for (int k = 0; k < sloupce; k++)
            {
                vysledek.matice[i][j] += (matice[i][k] * matice_2.matice[k][j]);
            }
        }
    }
    return vysledek;
}

template<typename T>
Matice<T> Matice<T>::transponuj_matici()
{
    Matice<T> vysledek(sloupce, radky, static_cast<T>(0));
    for (int i = 0; i < sloupce; i++)
    {
        for (int j = 0; j < radky; j++)
        {
            vysledek.matice[i][j] = matice[j][i];
        }
    }
    return vysledek;
}

template<typename T>
Matice<T> Matice<T>::skalarni_nasobeni(T scalar)
{
    Matice<T> vysledek(radky, sloupce, static_cast<T>(0));
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek.matice[i][j] = matice[i][j] * scalar;
        }
    }
    return vysledek;
}

template<typename T>
T Matice<T>::determinant_matice()
{
    T vysledek = 0;
    for (int i = 0; i < radky; i++)
    {
        for (int j = 0; j < sloupce; j++)
        {
            vysledek += matice[i][j];
        }
    }
    return vysledek;
}

template<typename T>
Matice<T>::~Matice()
{
    if (matice != nullptr)
    {
        for (int i = 0; i < radky; ++i)
        {
            delete[] matice[i];
        }
        delete[] matice;
        matice = nullptr;
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Matice<T> &m)
{
    os << "Matice (" << m.radky << "x" << m.sloupce << "):" << std::endl;
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

#endif
