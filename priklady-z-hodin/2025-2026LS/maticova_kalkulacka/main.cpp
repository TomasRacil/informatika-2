#include <iostream>

struct Matice {
  int** matice;
  int radky = 3;
  int sloupce = 3;
};

Matice* vytvor_matici(int radky, int sloupce){
  Matice* nova_matice =  new Matice;
  nova_matice->matice = nullptr;
  nova_matice->radky = radky;
  nova_matice->sloupce = sloupce;

  nova_matice->matice = new int*[nova_matice->radky]; 

  for (int i = 0; i < nova_matice->radky; ++i) {
      nova_matice->matice[i] = new int[nova_matice->sloupce];
      for (int j = 0; j < nova_matice->sloupce; j++) {
        nova_matice->matice[i][j] = rand() % 10;
    }
  }
  return nova_matice;
}

void smaz_matici(Matice*& matice){
  for (int i = 0; i < matice->radky; ++i) {
    delete[] matice->matice[i];
    matice->matice[i] = nullptr;
  }
  delete[] matice->matice;
  matice = nullptr; 
}

void vypis_matici(const Matice &matice) {
  std::cout << "Matice:" << std::endl;
  for (int i = 0; i < matice.radky; i++) {
    for (int j = 0; j < matice.sloupce; j++) {
      std::cout << matice.matice[i][j] << " ";
      ;
    }
    std::cout << std::endl;
  }
}

Matice *secti_matice(const Matice &matice_1, const Matice &matice_2) {
  std::cout << "Soucet matic (dynamic allocation):" << std::endl;
  Matice *vysledek = vytvor_matici(matice_1.radky,matice_1.sloupce);
  for (int i = 0; i < matice_1.radky; i++) {
    for (int j = 0; j < matice_1.sloupce; j++) {
      vysledek->matice[i][j] = matice_1.matice[i][j] + matice_2.matice[i][j];
    }
  }
  return vysledek;
}

Matice *nasob_matice(const Matice &matice_1, const Matice &matice_2) {
  std::cout << "Soucin matic:" << std::endl;
  Matice *vysledek = vytvor_matici(matice_1.radky,matice_1.sloupce);
  for (int i = 0; i < matice_1.radky; i++) {
    for (int j = 0; j < matice_2.sloupce; j++) {
      vysledek->matice[i][j] = 0;
      for (int k = 0; k < matice_1.sloupce; k++) {
        int h1 = matice_1.matice[i][k];
        int h2 = matice_2.matice[k][j];
        vysledek->matice[i][j] += (h1 * h2);
      }
    }
  }
  return vysledek;
}

int main() {

  Matice* maticeA = vytvor_matici(10,10);
  Matice* maticeB = vytvor_matici(10,10);
  vypis_matici(*maticeA);
  vypis_matici(*maticeB);
  Matice* soucet = secti_matice(*maticeA, *maticeB);
  vypis_matici(*soucet);
  Matice* nasobek = nasob_matice(*maticeA, *maticeB);
  vypis_matici(*nasobek);
  smaz_matici(maticeA);
  smaz_matici(maticeB);
  smaz_matici(soucet);
  smaz_matici(nasobek);


  // int matice_1[3][3]={{1,1,1},{1,1,1},{1,1,1}};
  // int matice_2[3][3];
  // int matice_3[3][3];

  // vypis_matici(matice_1, 3);

  // napln_matici(matice_2, 3);

  // vypis_matici(matice_2, 3);

  // nasob_matice(matice_1,matice_2, matice_3, 3);

  // vypis_matici(matice_3, 3);

  // Matice matice_1;
  // Matice matice_2;
  // Matice matice_3;

  // napln_matici(&matice_1); // Posíláme adresu (pointer)
  // napln_matici(&matice_2);

  // vypis_matici(matice_1); // Předáváme referencí (vypadá jako value)
  // vypis_matici(matice_2);

  // secti_matice(matice_1, matice_2, matice_3);
  // vypis_matici(matice_3);

  // nasob_matice(matice_1, matice_2, matice_3);
  // vypis_matici(matice_3);

  // std::cout << "\n--- Ukazka dynamicke alokace ---" << std::endl;

  // // Použití verze, která vrací pointer
  // Matice *dynamicky_soucet = secti_matice_new(matice_1, matice_2);
  // vypis_matici(*dynamicky_soucet); // Musíme dereferencovat pro výpis (pokud
  //                                  // bere referenci)

  // Matice *dynamicky_soucin = nasob_matice_new(matice_1, matice_2);
  // vypis_matici(*dynamicky_soucin);

  // // DŮLEŽITÉ: Paměť alokovanou pomocí 'new' musíme uvolnit pomocí 'delete'
  // delete dynamicky_soucet;
  // delete dynamicky_soucin;

  return 0;
}