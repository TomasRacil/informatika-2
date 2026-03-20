#include <string>  
#include <fstream>  
#include <iostream>

using namespace std;

int main(){

    ifstream soubor("data.txt");  
    string radek;
    int suma= 0;

    if (soubor.is_open()) {  
        while (getline(soubor, radek)) {
            int prvni_cislo, druhe_cislo;
            for(int i=0;i<radek.length();i++){
                if(isdigit(radek[i])){
                    prvni_cislo = radek[i]-'0';
                    break;
                } 
            }
            for(int i = radek.length()-1; i>=0;i--){
                if(isdigit(radek[i])){
                    druhe_cislo = radek[i]-'0';
                    break;
                }
            }
            int celkem_cislo = prvni_cislo*10 + druhe_cislo;
            suma+=celkem_cislo;
        }  
        soubor.close();  
    }


    cout<<suma<<endl;
    return 0;
}
