#include <iostream>
#include <string>
#include <fstream>

int main()
{
    std::ifstream vstupniSoubor("data.txt");
    int patro = 0;
    int basementPostiton = 0;
    std::string radek;
    // std::cin >> radek;
    if (vstupniSoubor.is_open()) {
        std::getline(vstupniSoubor, radek);
        vstupniSoubor.close();
    } else {
        std::cerr << "Nepodařilo se otevřít soubor." << std::endl;
        return 1;
    }
    // int pocitadlo=0;
    // for (char znak:radek){
    //     if (znak == '(')
    //     {
    //         patro++;
    //     }
    //     else
    //     {
    //         patro--;
    //     }
    //     pocitadlo++;
    //     if (patro==-1){
    //         std::cout<<pocitadlo<<std::endl;
    //         break;
    //     }
    // }
    for (int i = 0; i<radek.length(); i++)
    {
        // std::cout << s[i] << std::endl;
        if (radek[i] == '(')
        {
            patro++;
        }
        else
        {
            patro--;
        }
        if(patro==-1 && basementPostiton == 0){
            basementPostiton = i+1;
        }
    }

    std::cout << patro << std::endl;
    std::cout << basementPostiton <<std::endl;
    return 0;
}