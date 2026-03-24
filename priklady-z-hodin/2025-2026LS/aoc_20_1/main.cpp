#include <string>  
#include <fstream>  
#include <iostream>
#include <vector>

using namespace std;

int main(){

    ifstream soubor("data.txt");  
    string radek;
    vector<int> cisla;

    if (soubor.is_open()) {  
        while (getline(soubor, radek)) {
            cisla.push_back(stoi(radek));
        }  
        soubor.close();  
    }

    for(int i = 0; i<cisla.size();i++){
        std::cout<< cisla[i]<<std::endl;
    }

    return 0;
}
