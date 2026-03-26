#include <iostream>

void vypis_matici(int matice[][3], int radky){

    std::cout<<"Matice:"<<std::endl;
    for(int i = 0; i<radky; i++){
        for(int j=0;j<3;j++){
            std::cout<<matice[i][j]<<" ";;
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

void secti_matice(int matice_1[][3],int matice_2[][3], int matice_3[][3] , int radky){
    std::cout<<"Soucet matic:"<<std::endl;
    for(int i = 0; i<radky; i++){
        for(int j=0;j<3;j++){
            matice_3[i][j]=matice_1[i][j]+matice_2[i][j];
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

int main(){

    int matice_1[3][3]={{1,1,1},{1,1,1},{1,1,1}};
    int matice_2[3][3];
    int matice_3[3][3];

    vypis_matici(matice_1, 3);

    napln_matici(matice_2, 3);

    vypis_matici(matice_2, 3);

    nasob_matice(matice_1,matice_2, matice_3, 3);

    vypis_matici(matice_3, 3);

    return 0;
}