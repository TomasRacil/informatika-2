#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string>

int vytvor_nahodne_cislo(int od_cisla, int do_cisla);
bool hadej_cislo(int hadane_cislo);
void hrej_hru(int od_cisla, int do_cisla);

int main()
{
    srand(std::time(0));

    // if (hadej_cislo(vytvor_nahodne_cislo(3, 15)))
    // {
    //     std::cout << "Gratuluji";
    // }

    hrej_hru(0,10);

    return 0;
}

int vytvor_nahodne_cislo(int od_cisla, int do_cisla)
{
    int nah_cislo = (rand() % (do_cisla - od_cisla + 1)) + od_cisla;
    return nah_cislo;
}

bool hadej_cislo(int hadane_cislo)
{
    std::string tip;
    while (true)
    {
        std::cout << "Zadej svuj tip (nebo x pro ukonceni): ";
        std::cin >> tip;
        try
        {
            int tip_c = std::stoi(tip);
            if (tip_c == hadane_cislo)
            {
                std::cout << "Uhodl jsi cislo!" << std::endl;
                return true;
            }
            if (tip_c < hadane_cislo)
            {
                std::cout << "Tvuj tip je mensi jak hadane cislo." << std::endl;
            }
            else if (tip_c > hadane_cislo)
            {
                std::cout << "Tvuj tip je vetsi jak hadane cislo." << std::endl;
            }
        }
        catch (std::exception e)
        {
            if(tip=="x"){
                return false;
            }
            std::cout<<"Toto neni platna volba!"<<std::endl; 
        }
    }
}

void hrej_hru(int od_cisla, int do_cisla)
{
    std::cout << "Vitej ve hre uhadni cislo!";
    std::cout << "Tvym cilem je hadat cislo od " << od_cisla << " do " << do_cisla << std::endl;
    std::string volba;
    while (true)
    {
        if (hadej_cislo(vytvor_nahodne_cislo(od_cisla, do_cisla)) == true)
        {
            std::cout << "Gratuluji chces pokracovat? (A-ano, ostatni-ne)" << std::endl;
        }
        else
        {
            std::cout<<"Bohuzel jsi neuhadl chces to zkusit znovu? (A-ano, ostatni-ne)" << std::endl;
        }
        std::cin >> volba;
        if (volba != "A")
        {
            break;
        }
    }
}
