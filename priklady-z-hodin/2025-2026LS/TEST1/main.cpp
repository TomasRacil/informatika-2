#include <iostream>

using namespace std;

int dalsiKrok(int n) {
    if (n % 2 == 0) {
        return n / 2;
    } else {
        return 3 * n + 1;
    }
}

void zpracujPosloupnost(int n) {
    int pocetKroku = 0;
    
    cout << "Posloupnost: " << n;

    while (n != 1) {
        n = dalsiKrok(n);
        cout << " -> " << n;
        pocetKroku++;
    }
    
    cout << endl << "Pocet kroku: " << pocetKroku << endl << endl;
}

int main() {
    int cislo;

    while (true) {
        cout << "Zadejte kladne cislo (0 nebo zaporne pro ukonceni): ";
        cin >> cislo;

        if (cislo <= 0) {
            cout << "Konec programu." << endl;
            break;
        }
        zpracujPosloupnost(cislo);
    }

    return 0;
}