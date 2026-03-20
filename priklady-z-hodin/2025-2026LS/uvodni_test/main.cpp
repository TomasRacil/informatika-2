#include <iostream>
#include <string>
#include <vector>

// ==========================================
// Úloha 1: Rostoucí posloupnost
// ==========================================
int nejdelsi_rostouci(std::vector<int> pole) {
  if (pole.empty())
    return 0;

  int max_delka = 1;
  int aktualni_delka = 1;

  for (size_t i = 1; i < pole.size(); i++) {
    if (pole[i] > pole[i - 1]) {
      aktualni_delka++;
    } else {
      if (aktualni_delka > max_delka) {
        max_delka = aktualni_delka;
      }
      aktualni_delka = 1;
    }
  }
  if (aktualni_delka > max_delka) {
    max_delka = aktualni_delka;
  }

  return max_delka;
}

// ==========================================
// Úloha 2: Validace data
// ==========================================
bool je_platne_datum(int den, int mesic, int rok) {
  if (rok < 1 || mesic < 1 || mesic > 12 || den < 1) {
    return false;
  }

  int dny_v_mesici = 31;

  if (mesic == 4 || mesic == 6 || mesic == 9 || mesic == 11) {
    dny_v_mesici = 30;
  } else if (mesic == 2) {
    bool je_prestupny = (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
    if (je_prestupny){
      dny_v_mesici = 29;
    }
    else{
      dny_v_mesici = 28;
    }
    // dny_v_mesici = je_prestupny ? 29 : 28;
  }

  return den <= dny_v_mesici;
}

// ==========================================
// Úloha 3: Rekurze (Součet cifer)
// ==========================================
int soucet_cifer(int cislo) {
  if (cislo == 0) {
    return 0;
  }
  int posledni_cislo = cislo % 10;
  int zbytek = cislo / 10;
  return posledni_cislo + soucet_cifer(zbytek);
}

// ==========================================
// Úloha 4: Komprese (RLE)
// ==========================================
void komprese_rle(std::string text) {
  if (text.empty())
    return;

  int pocet = 1;
  char aktualni_znak = text[0];

  for (size_t i = 1; i < text.length(); i++) {
    if (text[i] == aktualni_znak) {
      pocet++;
    } else {
      std::cout << pocet << aktualni_znak;
      aktualni_znak = text[i];
      pocet = 1;
    }
  }
  std::cout << pocet << aktualni_znak << std::endl;
}

// ==========================================
// Hlavní funkce pro otestování kódů
// ==========================================
int main() {
  std::cout << "--- Test Uloha 1: Rostouci posloupnost ---" << std::endl;
  std::vector<int> pole1 = {5, 1, 3, 5, 2, 8};
  std::cout << "Vstup: [5, 1, 3, 5, 2, 8] | Vystup: " << nejdelsi_rostouci(pole1) << " (ocekavano 3)" << std::endl;
  std::vector<int> pole2 = {1, 2, 3, 4, 5};
  std::cout << "Vstup: [1, 2, 3, 4, 5]    | Vystup: " << nejdelsi_rostouci(pole2) << " (ocekavano 5)" << std::endl;
  std::vector<int> pole3 = {5, 4, 3, 2, 1};
  std::cout << "Vstup: [5, 4, 3, 2, 1]    | Vystup: " << nejdelsi_rostouci(pole3) << " (ocekavano 1)" << std::endl;
  std::vector<int> pole4 = {};
  std::cout << "Vstup: []                 | Vystup: " << nejdelsi_rostouci(pole4) << " (ocekavano 0)" << std::endl;

  std::vector<int> pole5 = {1, 2, 2, 3};
  std::cout << "Vstup: [1, 2, 2, 3]       | Vystup: " << nejdelsi_rostouci(pole5) << " (ocekavano 2 - neostre neni rostouci)" << std::endl;

  std::cout << "\n--- Test Uloha 2: Validace data ---" << std::endl;
  std::cout << "29.2.2024: " << je_platne_datum(29, 2, 2024) << " (ocek. 1)" << std::endl;
  std::cout << "29.2.2023: " << je_platne_datum(29, 2, 2023) << " (ocek. 0)" << std::endl;
  std::cout << "29.2.2000: " << je_platne_datum(29, 2, 2000) << " (ocek. 1)" << std::endl;
  std::cout << "29.2.1900: " << je_platne_datum(29, 2, 1900) << " (ocek. 0)" << std::endl;
  std::cout << "30.2.2024: " << je_platne_datum(30, 2, 2024) << " (ocek. 0)" << std::endl;
  std::cout << "31.4.2024: " << je_platne_datum(31, 4, 2024) << " (ocek. 0)" << std::endl;
  std::cout << "31.6.2024: " << je_platne_datum(31, 6, 2024) << " (ocek. 0)" << std::endl;

  std::cout << "\n--- Test Uloha 3: Soucet cifer ---" << std::endl;
  std::cout << "451:   " << soucet_cifer(451) << " (ocek. 10)" << std::endl;
  std::cout << "0:     " << soucet_cifer(0) << " (ocek. 0)" << std::endl;
  std::cout << "9:     " << soucet_cifer(9) << " (ocek. 9)" << std::endl;
  std::cout << "12345: " << soucet_cifer(12345) << " (ocek. 15)" << std::endl;

  std::cout << "\n--- Test Uloha 4: Komprese RLE ---" << std::endl;
  std::cout << "AAAABBBCCDAA -> ";
  komprese_rle("AAAABBBCCDAA");
  std::cout << "ABCDE        -> ";
  komprese_rle("ABCDE");
  std::cout << "AAAAA        -> ";
  komprese_rle("AAAAA");
  std::cout << "(prazdny)     -> ";
  komprese_rle("");

  return 0;
}