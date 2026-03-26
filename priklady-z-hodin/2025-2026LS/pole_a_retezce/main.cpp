#include <iostream>

void vypis_pole(int cisla[], int velikost){
    std::cout<<"Obsah pole: "<<std::endl;
    for(int i=0; i<velikost; i++){
        std::cout<<cisla[i]<<", ";
    }
    std::cout<<std::endl;
}

int nejmensi(int cisla[], int velikost){
    int nejmensi= cisla[0];
    for(int i=1; i<velikost; i++){
        if (cisla[i]<nejmensi) nejmensi=cisla[i];
    }
    return nejmensi;
}

void napln_pole(int cisla[], int velikost){
    std::cout<<"Zadej cisla do pole: "<<std::endl;
    for(int i=0; i<velikost; i++){
        std::cin>>cisla[i];
    }
}

int main(){
    int cisla[5];

    vypis_pole(cisla,5);

    napln_pole(cisla,5);

    vypis_pole(cisla,5);

    std::cout<<"Nejmensi cislo je: "<<nejmensi(cisla, 5)<<std::endl;

    std::string jmeno = "Tomas";
    std::string prijmeni = "Racil";

    std::cout<< jmeno + " " + prijmeni<<std::endl;

}