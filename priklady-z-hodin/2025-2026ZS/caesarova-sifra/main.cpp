#include <iostream>
#include <string>


std::string sifruj(std::string vstup, int posun){
    std::string vystup;
    for(char znak:vstup){
        char ch = tolower(znak);
        if (96<ch && ch<123){
            int hodnota = ch - 'a';
            hodnota = (hodnota + posun) % 26;
            vystup += (char)(hodnota + 'a');
        }else{
            vystup+=ch;
        }
        
    }
    return vystup;
}


int main(){
    std::cout<<sifruj("Testovaci text",3);
    return 0;
}