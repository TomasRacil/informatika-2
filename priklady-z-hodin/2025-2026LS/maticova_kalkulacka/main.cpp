#include <iostream>

struct Matice {
  int **matice;
  int radky;
  int sloupce;
};

Matice *vytvor_matici(int radky, int sloupce, int inicializacni_hodnota = NULL);
void smaz_matici(Matice *&matice);
void vypis_matici(Matice *matice);
Matice *secti_matice(const Matice &matice_1, const Matice &matice_2);
Matice *nasob_matice(const Matice &matice_1, const Matice &matice_2);
Matice *transponuj_matici(const Matice &matice);
Matice *skalarni_nasobeni(const Matice &matice, int scalar);
int determinant_matice(const Matice &matice);

int main() {
  srand(time(0));

  std::cout << "Zadej pocet radku prvni matice: ";
  int radkyA;
  std::cin >> radkyA;

  std::cout << "Zadej pocet sloupcu prvni matice: ";
  int sloupceA;
  std::cin >> sloupceA;

  Matice *maticeA = vytvor_matici(radkyA, sloupceA);

  std::cout << "Zadej pocet radku druhe matice: ";
  int radkyB;
  std::cin >> radkyB;

  std::cout << "Zadej pocet sloupcu druhe matice: ";
  int sloupceB;
  std::cin >> sloupceB;

  Matice *maticeB = vytvor_matici(radkyB, sloupceB);

  vypis_matici(maticeA);
  vypis_matici(maticeB);

  std::cout << "Soucet matic A a B:" << std::endl;
  Matice *soucet = secti_matice(*maticeA, *maticeB);
  vypis_matici(soucet);

  std::cout << "Soucin matic A a B:" << std::endl;
  Matice *nasobek = nasob_matice(*maticeA, *maticeB);
  vypis_matici(nasobek);

  std::cout << "Transponovana maticeA:" << std::endl;
  Matice *transponovany_maticeA = transponuj_matici(*maticeA);
  vypis_matici(transponovany_maticeA);

  std::cout << "Skalarni nasobeni maticeA cislem 2:" << std::endl;
  Matice *skalarni = skalarni_nasobeni(*maticeA, 2);
  vypis_matici(skalarni);

  int determinant_maticeA = determinant_matice(*maticeA);
  std::cout << "Determinant matice A: " << determinant_maticeA << std::endl;
  int determinant_maticeB = determinant_matice(*maticeB);
  std::cout << "Determinant matice B: " << determinant_maticeB << std::endl;

  smaz_matici(maticeA);
  smaz_matici(maticeB);
  smaz_matici(soucet);
  smaz_matici(nasobek);
  smaz_matici(transponovany_maticeA);
  smaz_matici(skalarni);

  return 0;
}

Matice *vytvor_matici(int radky, int sloupce, int inicializacni_hodnota) {
  Matice *nova_matice = new Matice;
  nova_matice->matice = nullptr;
  nova_matice->radky = radky;
  nova_matice->sloupce = sloupce;

  nova_matice->matice = new int *[nova_matice->radky];

  for (int i = 0; i < nova_matice->radky; ++i) {
    nova_matice->matice[i] = new int[nova_matice->sloupce];
    for (int j = 0; j < nova_matice->sloupce; j++) {
      if (inicializacni_hodnota == NULL) {
        nova_matice->matice[i][j] = rand() % 10;
      } else {
        nova_matice->matice[i][j] = inicializacni_hodnota;
      }
    }
  }
  return nova_matice;
}

void smaz_matici(Matice *&matice) {
  if (matice == nullptr) {
    return;
  }
  for (int i = 0; i < matice->radky; ++i) {
    delete[] matice->matice[i];
    matice->matice[i] = nullptr;
  }
  delete[] matice->matice;
  matice = nullptr;

  delete matice;
  matice = nullptr;
}

void vypis_matici(Matice *matice) {
  std::cout << "Matice:" << std::endl;
  if (matice == nullptr) {
    std::cout << "Matice je prazdna." << std::endl;
    return;
  }
  for (int i = 0; i < matice->radky; i++) {
    for (int j = 0; j < matice->sloupce; j++) {
      std::cout << matice->matice[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

Matice *secti_matice(const Matice &matice_1, const Matice &matice_2) {
  if (matice_1.radky != matice_2.radky ||
      matice_1.sloupce != matice_2.sloupce) {
    std::cout << "Matice nejsou stejne velke." << std::endl;
    return nullptr;
  }
  Matice *vysledek = vytvor_matici(matice_1.radky, matice_1.sloupce, 0);
  for (int i = 0; i < matice_1.radky; i++) {
    for (int j = 0; j < matice_1.sloupce; j++) {
      vysledek->matice[i][j] = matice_1.matice[i][j] + matice_2.matice[i][j];
    }
  }
  return vysledek;
}

Matice *nasob_matice(const Matice &matice_1, const Matice &matice_2) {
  if (matice_1.sloupce != matice_2.radky) {
    std::cout << "Matice nejsou kompatibilni pro nasobeni." << std::endl;
    return nullptr;
  }
  Matice *vysledek = vytvor_matici(matice_1.radky, matice_2.sloupce, 0);
  for (int i = 0; i < matice_1.radky; i++) {
    for (int j = 0; j < matice_2.sloupce; j++) {
      for (int k = 0; k < matice_1.sloupce; k++) {
        vysledek->matice[i][j] +=
            (matice_1.matice[i][k] * matice_2.matice[k][j]);
      }
    }
  }
  return vysledek;
}

Matice *transponuj_matici(const Matice &matice) {
  Matice *vysledek = vytvor_matici(matice.sloupce, matice.radky, 0);
  for (int i = 0; i < matice.sloupce; i++) {
    for (int j = 0; j < matice.radky; j++) {
      vysledek->matice[i][j] = matice.matice[j][i];
    }
  }
  return vysledek;
}

Matice *skalarni_nasobeni(const Matice &matice, int scalar) {
  Matice *vysledek = vytvor_matici(matice.radky, matice.sloupce, 0);
  for (int i = 0; i < matice.radky; i++) {
    for (int j = 0; j < matice.sloupce; j++) {
      vysledek->matice[i][j] = matice.matice[i][j] * scalar;
    }
  }
  return vysledek;
}

int determinant_matice(const Matice &matice) {
  int vysledek = 0;
  for (int i = 0; i < matice.radky; i++) {
    for (int j = 0; j < matice.sloupce; j++) {
      vysledek += matice.matice[i][j];
    }
  }
  return vysledek;
}
