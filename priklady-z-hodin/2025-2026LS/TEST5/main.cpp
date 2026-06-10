#include <iostream>
#include "Vybaveni.h"
#include "PalnaZbran.h"
#include "BalistickaOchrana.h"

using namespace std;

int main() {
    cout << "Pocatocni pocet kusu vybaveni: " << Vybaveni::getPocetKusu() << endl << endl;

    cout << "--- Vytvoreni vojenskeho vybaveni ---" << endl;
    PalnaZbran* zbran1 = new PalnaZbran("M4A1", 3.5, 800);
    PalnaZbran* zbran2 = new PalnaZbran("M203", 1.5, 100);
    BalistickaOchrana* ochrana = new BalistickaOchrana("Vesta-NIJ4", 5.0, 4);

    cout << "Aktualni pocet kusu v evidenci: " << Vybaveni::getPocetKusu() << endl << endl;

    cout << "--- Test polymorfismu ---" << endl;
    Vybaveni* pole[3] = { zbran1, zbran2, ochrana };
    for (int i = 0; i < 3; i++) {
        pole[i]->pripravKAkci();
    }
    cout << endl;

    cout << "--- Test pretizeni operatoru ---" << endl;
    {
        PalnaZbran komplet = *zbran1 + *zbran2;
        cout << "Slouceny zbranovy system: " << komplet << endl;
        komplet.pripravKAkci();
    }
    cout << endl;

    cout << "--- Uklid pameti ---" << endl;
    delete zbran1;
    delete zbran2;
    delete ochrana;

    cout << "Konecny pocet kusu v evidenci: " << Vybaveni::getPocetKusu() << endl;

    return 0;
}
