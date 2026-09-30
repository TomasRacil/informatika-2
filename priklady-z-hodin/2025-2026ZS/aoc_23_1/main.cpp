#include <iostream>
#include <string>
#include <fstream>

std::string cisla[9] = {"one","two","three","four","five","six","seven","eight","nine"};

int preved_na_cislo(std::string retezec, int pozice){
    for(int i=0;i<9;i++){
        if(retezec.find(cisla[i], pozice)==pozice){
            return i+1;
        }
    }
    return 0;
}

int main(){

    std::ifstream soubor("data.txt");
    std::string radek;
    int suma = 0;
    if (!soubor.is_open()) {
        std::cout << "Soubor se nepodarilo otevrit pro cteni." << std::endl;
    }else{
        while(std::getline(soubor, radek)){
            std::string cislice;
            for(int i=0;i<radek.length();i++){
                if(isdigit(radek[i])){
                    cislice+=radek[i];
                    break;
                }
                int cislo = preved_na_cislo(radek,i);
                if(cislo!=0){
                    cislice+=std::to_string(cislo);
                    break;
                }
            }
            for(int i=radek.length()-1;i>=0;i--){
                if(isdigit(radek[i])){
                    cislice+=radek[i];
                    break;
                }
                int cislo = preved_na_cislo(radek,i);
                if(cislo!=0){
                    cislice+=std::to_string(cislo);
                    break;
                }
            }
            suma+=std::stoi(cislice);
        }

        std::cout<<suma<<std::endl;
        
        // std::getline(soubor, radek);
        // std::cout<<radek<<std::endl;
        // std::getline(soubor, radek);
        // std::cout<<radek<<std::endl;
    }
    return 0;
}




// #include <iostream>
// #include <string>
// #include <fstream>

// int main()
// {
//     std::ifstream vstupniSoubor("data.txt");
//     int suma = 0;
//     std::string radek;
//     if (vstupniSoubor.is_open()) {
//         while (std::getline(vstupniSoubor, radek))
//         {
//             std::string cislo;
//             for (char znak : radek) {
//             if (znak >= '0' && znak <= '9') {
//                 cislo += znak;
//                 break;
//             }
//             }
//             for (int i = radek.length()-1; i >=0; i--) {
//                 if (radek[i] >= '0' && radek[i] <= '9') {
//                     cislo += radek[i];
//                     break;
//                 }
//             }
//             suma += std::stoi(cislo);
//         }
        
//         vstupniSoubor.close();
//     } else {
//         std::cerr << "Nepodařilo se otevřít soubor." << std::endl;
//         return 1;
//     }
//     std::cout << suma << std::endl;
//     return 0;
// }