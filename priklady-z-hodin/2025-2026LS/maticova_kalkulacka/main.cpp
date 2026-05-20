#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

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
  Matice nasob_matice(const Matice &matice_2);
  Matice transponuj_matici();
  Matice skalarni_nasobeni(int scalar);
  int determinant_matice();
  ~Matice();
};

int main()
{
  srand(time(0));

  std::cout << "Zadej pocet radku prvni matice: ";
  int radkyA;
  std::cin >> radkyA;

  std::cout << "Zadej pocet sloupcu prvni matice: ";
  int sloupceA;
  std::cin >> sloupceA;

  Matice maticeA = Matice(radkyA, sloupceA);

  std::cout << "Zadej pocet radku druhe matice: ";
  int radkyB;
  std::cin >> radkyB;

  std::cout << "Zadej pocet sloupcu druhe matice: ";
  int sloupceB;
  std::cin >> sloupceB;

  Matice maticeB = Matice(radkyB, sloupceB);

  maticeA.vypis_matici();
  maticeB.vypis_matici();

  std::cout << "Soucet matic A a B:" << std::endl;
  Matice soucet = maticeA.secti_matice(maticeB);
  soucet.vypis_matici();

  std::cout << "Soucin matic A a B:" << std::endl;
  Matice soucin = maticeA.nasob_matice(maticeB);
  soucin.vypis_matici();

  std::cout << "Transponovana maticeA:" << std::endl;
  Matice transponovany_maticeA = maticeA.transponuj_matici();
  transponovany_maticeA.vypis_matici();

  std::cout << "Skalarni nasobeni maticeA cislem 2:" << std::endl;
  Matice skalarni = maticeA.skalarni_nasobeni(2);
  skalarni.vypis_matici();

  std::cout << "Determinant maticeA: " << maticeA.determinant_matice() << std::endl;
  std::cout << "Determinant maticeB: " << maticeB.determinant_matice() << std::endl;

  return 0;
}


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

Matice Matice::nasob_matice(const Matice &matice_2)
{
  if (sloupce != matice_2.radky) {
    throw std::runtime_error("Matice nejsou kompatibilni pro nasobeni.");
  }
  Matice vysledek = Matice(radky, matice_2.sloupce, 0);
  for (int i = 0; i < radky; i++) {
    for (int j = 0; j < matice_2.sloupce; j++) {
      for (int k = 0; k < sloupce; k++) {
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
  for (int i = 0; i < sloupce; i++) {
    for (int j = 0; j < radky; j++) {
      vysledek.matice[i][j] = matice[j][i];
    }
  }
  return vysledek;
}

Matice Matice::skalarni_nasobeni(int scalar)
{
  Matice vysledek = Matice(radky, sloupce, 0);
  for (int i = 0; i < radky; i++) {
    for (int j = 0; j < sloupce; j++) {
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
