#include <iostream>
#include <ctime>
#include "Matice.h"


int main()
{
  srand(time(0));

  std::cout << "Zadej pocet radku prvni matice: ";
  int radkyA;
  std::cin >> radkyA;

  std::cout << "Zadej pocet sloupcu prvni matice: ";
  int sloupceA;
  std::cin >> sloupceA;

  Matice<double> maticeA(radkyA, sloupceA);

  std::cout << "Zadej pocet radku druhe matice: ";
  int radkyB;
  std::cin >> radkyB;

  std::cout << "Zadej pocet sloupcu druhe matice: ";
  int sloupceB;
  std::cin >> sloupceB;

  Matice<double> maticeB(radkyB, sloupceB);

  maticeA.vypis_matici();
  maticeB.vypis_matici();

  std::cout << "Soucet matic A a B:" << std::endl;
  Matice<double> soucet = maticeA + maticeB;
  soucet.vypis_matici();

  std::cout << "Soucin matic A a B:" << std::endl;
  Matice<double> soucin = maticeA.nasob_matice(maticeB);
  soucin.vypis_matici();

  std::cout << "Transponovana maticeA:" << std::endl;
  Matice<double> transponovany_maticeA = maticeA.transponuj_matici();
  transponovany_maticeA.vypis_matici();

  std::cout << "Skalarni nasobeni maticeA cislem 2:" << std::endl;
  Matice<double> skalarni = maticeA.skalarni_nasobeni(2);
  skalarni.vypis_matici();

  std::cout << "Determinant maticeA: " << maticeA.determinant_matice() << std::endl;

  return 0;
}