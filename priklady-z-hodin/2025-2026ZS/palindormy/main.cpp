#include <string>
#include <iostream>
#include <algorithm>

bool jePalindrom1(std::string text){
    std::string obracene = text;
    std::reverse(obracene.begin(), obracene.end());
    return obracene == text;
}

bool jePalindrom2(std::string text){
    bool jePalindrom = true;
    for(int i = 0; i<text.size(); i++){
        char zacatek = *(text.begin()+i);
        char konec = *(text.end()-i-1);
        jePalindrom = zacatek == konec;
        if (jePalindrom ==  false) return false;
    }
    return true;
}

bool jePalindrom3(std::string text){
    int leva = 0;
    int prava = text.size()-1;
    while (leva<prava)
    {
        if (text[leva] == ' '){
            leva++;
        }
        if (text[prava] == ' '){
            prava--;
        }
        if (text[leva]!=text[prava]){
            return false;
        }
        leva++;
        prava--;
    }
    return true;
    
}

int main(){

    std::cout<<jePalindrom3("jelenovi pivo nelej")<<std::endl;

    return 0;
}