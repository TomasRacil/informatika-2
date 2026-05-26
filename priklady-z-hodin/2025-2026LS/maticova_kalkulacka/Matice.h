#pragma once

#include <cstdlib>
#include <iostream>

class Matice
{
private:
  int **matice;
  int radky;
  int sloupce;

public:
  Matice(int radky, int sloupce, int inicializacni_hodnota = NULL);
  Matice(const Matice &other);
  void vypis_matici();
  Matice secti_matice(const Matice &matice_2);
  Matice operator+(const Matice &matice_2);
  Matice nasob_matice(const Matice &matice_2);
  Matice transponuj_matici();
  Matice skalarni_nasobeni(int scalar);
  int determinant_matice();
  friend std::ostream& operator<<(std::ostream& os, const Matice& m);
  ~Matice();
};