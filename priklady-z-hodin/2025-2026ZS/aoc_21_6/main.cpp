#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<int> nacti_data(std::string filename){
    std::ifstream soubor(filename);
    if (!soubor.is_open())
    {
        std::cerr << "Chyba: Soubor '" << filename << "' se nepodařilo otevřít!" << std::endl;
    }
    std::vector<int> ryby;
    std::string radek, ryba;
    std::getline(soubor, radek);
    std::stringstream ss(radek);
    while(std::getline(ss, ryba, ',')){
        ryby.push_back(std::stoi(ryba));
    }
    return ryby;
};

std::ostream& operator<<(std::ostream& os, const std::vector<int>& ryby) {
    os <<  "Pocet ryb: " << ryby.size()<<std::endl;
    return os; 
}
void vytiskni_ryby(std::vector<int> ryby){
    std::cout << "Ryby: ";
    for(auto r: ryby){
        std::cout << r << ", ";
    }
    std::cout << std::endl;
};

void simuluj_ryby(std::vector<int>* ryby, int dny){
    for (int den = 0; den < dny; den++){
        int pocet_novych_ryb = 0;
        for(size_t i = 0; i < ryby->size(); i++){
            (*ryby)[i]--;
            if((*ryby)[i] < 0){
                (*ryby)[i] = 6;
                pocet_novych_ryb++;
            }
        }
        for(int j = 0; j < pocet_novych_ryb; j++){
            ryby->push_back(8);
        }
        std::cout << den<<std::endl;
        std::cout << *ryby;
        // vytiskni_ryby(*ryby);
    }
}

int main(){
    std::string filename = "data.txt";
    std::vector<int> ryby = nacti_data(filename);
    vytiskni_ryby(ryby);
    simuluj_ryby(&ryby, 256);
    return 0;

}