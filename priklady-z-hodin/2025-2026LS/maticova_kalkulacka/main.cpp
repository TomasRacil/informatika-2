#include <iostream>

struct Matice
{
    int matice[3][3];
    int radky=3;
    int sloupce=3;
};


void vypis_matici(int matice[][3], int radky){
    std::cout<<"Matice:"<<std::endl;
    for(int i = 0; i<radky; i++){
        for(int j=0;j<3;j++){
            std::cout<<matice[i][j]<<" ";;
        }
        std::cout<<std::endl;
    }
}

void vypis_matici(Matice matice){
    std::cout<<"Matice:"<<std::endl;
    for(int i = 0; i<matice.radky; i++){
        for(int j=0;j<matice.sloupce;j++){
            std::cout<<matice.matice[i][j]<<" ";;
        }
        std::cout<<std::endl;
    }
}

void napln_matici(int matice[][3], int radky){
    std::cout<<"Napln matici:"<<std::endl;
    for(int i = 0; i<radky; i++){
        for(int j=0;j<3;j++){
            // std::cin>>matice[i][j];
            matice[i][j]=rand()%10;
        }
    }
}

void napln_matici(Matice &matice){
    std::cout<<"Napln matici:"<<std::endl;
    for(int i = 0; i<matice.radky; i++){
        for(int j=0;j<matice.sloupce;j++){
            // std::cin>>matice
            matice.matice[i][j]=rand()%10;
        }
    }
}

void secti_matice(int matice_1[][3],int matice_2[][3], int matice_3[][3] , int radky){
    std::cout<<"Soucet matic:"<<std::endl;
    for(int i = 0; i<radky; i++){
        for(int j=0;j<3;j++){
            matice_3[i][j]=matice_1[i][j]+matice_2[i][j];
        }
    }
}

void secti_matice(Matice matice_1, Matice matice_2, Matice &matice_3){
    std::cout<<"Soucet matic:"<<std::endl;
    for(int i = 0; i<matice_1.radky; i++){
        for(int j=0;j<matice_1.sloupce;j++){
            matice_3.matice[i][j]=matice_1.matice[i][j]+matice_2.matice[i][j];
        }
    }
}


void nasob_matice(int matice_1[][3],int matice_2[][3], int matice_3[][3] , int radky){
    std::cout<<"Soucin matic:"<<std::endl;
    for(int i = 0; i<radky; i++){
        for(int j=0;j<3;j++){
            matice_3[i][j]=0;
            for(int k=0;k<3;k++){
                int h1 = matice_1[i][k];
                int h2 = matice_2[k][j];
                matice_3[i][j]+=(h1*h2);
            }
        }
    }
}

void nasob_matice(Matice matice_1, Matice matice_2, Matice &matice_3){
    std::cout<<"Soucin matic:"<<std::endl;
    for(int i = 0; i<matice_1.radky; i++){
        for(int j=0;j<matice_1.sloupce;j++){
            matice_3.matice[i][j]=0;
            for(int k=0;k<matice_1.sloupce;k++){
                int h1 = matice_1.matice[i][k];
                int h2 = matice_2.matice[k][j];
                matice_3.matice[i][j]+=(h1*h2);
            }
        }
    }
}


int main(){

    // int matice_1[3][3]={{1,1,1},{1,1,1},{1,1,1}};
    // int matice_2[3][3];
    // int matice_3[3][3];

    // vypis_matici(matice_1, 3);

    // napln_matici(matice_2, 3);

    // vypis_matici(matice_2, 3);

    // nasob_matice(matice_1,matice_2, matice_3, 3);

    // vypis_matici(matice_3, 3);

    Matice matice_1;
    Matice matice_2;
    Matice matice_3;

    napln_matici(matice_1);
    napln_matici(matice_2);

    vypis_matici(matice_1);
    vypis_matici(matice_2);

    secti_matice(matice_1,matice_2, matice_3);
    vypis_matici(matice_3);


    nasob_matice(matice_1,matice_2, matice_3);
    vypis_matici(matice_3);


    return 0;
}