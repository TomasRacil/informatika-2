#include <iostream>
#include <fstream>

using namespace std;

struct Mereni {
    int den;
    double teplota;
};

void ulozData() {
    ofstream vystupniSoubor("teploty.txt");
    
    if (!vystupniSoubor.is_open()) {
        cout << "Chyba pri otevirani souboru pro zapis!" << endl;
        return;
    }

    cout << "--- ZADANI DAT ---" << endl;
    for (int i = 1; i <= 7; i++) {
        double teplota;
        cout << "Zadejte teplotu pro " << i << ". den: ";
        cin >> teplota;
        
        vystupniSoubor << i << " " << teplota << endl;
    }
    
    vystupniSoubor.close();
    cout << "Data byla uspesne ulozena do souboru teploty.txt.\n\n";
}

void analyzujData() {
    const int POCET_DNI = 7;
    Mereni tyden[POCET_DNI];
    
    ifstream vstupniSoubor("teploty.txt");
    
    if (!vstupniSoubor.is_open()) {
        cout << "Chyba pri otevirani souboru pro cteni!" << endl;
        return;
    }

    int index = 0;
    while (vstupniSoubor >> tyden[index].den >> tyden[index].teplota && index < POCET_DNI) {
        index++;
    }
    vstupniSoubor.close();

    double soucet = 0.0;
    Mereni maxMereni = tyden[0];

    for (int i = 0; i < POCET_DNI; i++) {
        soucet += tyden[i].teplota;
        
        if (tyden[i].teplota > maxMereni.teplota) {
            maxMereni = tyden[i];
        }
    }

    cout << "--- ANALYZA DAT ZE SOUBORU ---" << endl;
    cout << "Prumerna teplota: " << (soucet / POCET_DNI) << " stupnu." << endl;
    cout << "Nejtepleji bylo " << maxMereni.den << ". den s teplotou " 
         << maxMereni.teplota << " stupnu." << endl;
}

int main() {
    ulozData();
    analyzujData();
    
    return 0;
}