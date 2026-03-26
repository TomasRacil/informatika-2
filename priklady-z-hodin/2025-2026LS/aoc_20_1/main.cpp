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
        int prvni_cislo = cisla[i];
        for(int j = i+1; j<cisla.size(); j++){
            int druhe_cislo = cisla[j];
            if(prvni_cislo+druhe_cislo==2020){
                std::cout<<prvni_cislo*druhe_cislo<<std::endl;
                return 0;
            }
        }
    }

    return 0;
}
