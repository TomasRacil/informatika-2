#include <fstream>
#include <iostream>
#include <string>

bool zapisZaznamuDoSouboru(std::string filepath){
    std::string zaznam;
    std::cout<<"Zadej zaznam do denicku (nebo KONEC pro ukonceni): ";
    std::getline(std::cin, zaznam);
    if(zaznam == "KONEC"){
        return false;
    }else{
        std::ofstream vystupDoSouboru(filepath, std::ios::app);
        if (vystupDoSouboru.is_open()) {
            vystupDoSouboru << zaznam <<std::endl;  
            vystupDoSouboru.close();  
        }
        return true;
    }
}

void prectiSoubor(std::string filename){
    std::ifstream soubor(filename);  
    std::string radek;
    int cisloZapisu = 1;
    if (soubor.is_open()) {  
        while (std::getline(soubor, radek)) {  
            std::cout<< cisloZapisu<< ": " << radek << std::endl;  
            cisloZapisu++;
        }  
        soubor.close();  
    }
}

int main(){
    std::string filepath ="denicek.txt";

    prectiSoubor(filepath);
    // while (true)
    // {
    //     if(!zapisZaznamuDoSouboru(filepath)){
    //         break;
    //     }
    // }
    

    return 0;
}