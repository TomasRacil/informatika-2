#include <iostream>
#include <vector>

void zobraz_ryby(std::vector<int> ryby)
{
    // for(int i=0; i<ryby.size();i++){
    //     std::cout<<ryby[i]<<", ";
    // }
    for (int ryba : ryby)
    {
        std::cout << ryba << ", ";
    }
    std::cout << std::endl;
}

void reseni_jedna(std::vector<int> ryby, int pocet_dni_k_simulaci){
    for (int d = 0; d < pocet_dni_k_simulaci; d++)
    {
        std::cout<<d<<std::endl;
        int pocet_ryb_k_pridani = 0;
        for (int i = 0; i < ryby.size(); i++)
        {
            ryby[i]--;
            if (ryby[i] < 0)
            {
                ryby[i] = 6;
                pocet_ryb_k_pridani++;
            }
        }
        for (int i = 0; i < pocet_ryb_k_pridani; i++)
        {
            ryby.push_back(8);
        }
        // zobraz_ryby(ryby);
    }
    std::cout<<ryby.size()<<std::endl;
}

void zobraz_pole(long long pole[9]){
    for(int i=0;i<9;i++){
        std::cout<<pole[i]<<"|";
    }
    std::cout<<std::endl;
}

void posun(long long pole[9]){
    long long temp = pole[0];
    for(int i=0;i<9;i++){
        if(i==8){
            pole[i] = temp;
        }else{
            pole[i]=pole[i+1];
        }
    }
}

long long suma(long long pole[9]){
    long long suma=0;
    for(int i=0;i<9;i++){
        suma+=pole[i];
    }
    return suma;
}
int main()
{

    std::vector<int> ryby = {1,2,4,5,5,5,2,1,3,1,4,3,2,1,5,5,1,2,3,4,4,1,2,3,2,1,4,4,1,5,5,1,3,4,4,4,1,2,2,5,1,5,5,3,2,3,1,1,3,5,1,1,2,4,2,3,1,1,2,1,3,1,2,1,1,2,1,2,2,1,1,1,1,5,4,5,2,1,3,2,4,1,1,3,4,1,4,1,5,1,4,1,5,3,2,3,2,2,4,4,3,3,4,3,4,4,3,4,5,1,2,5,2,1,5,5,1,3,4,2,2,4,2,2,1,3,2,5,5,1,3,3,4,3,5,3,5,5,4,5,1,1,4,1,4,5,1,1,1,4,1,1,4,2,1,4,1,3,4,4,3,1,2,2,4,3,3,2,2,2,3,5,5,2,3,1,5,1,1,1,1,3,1,4,1,4,1,2,5,3,2,4,4,1,3,1,1,1,3,4,4,1,1,2,1,4,3,4,2,2,3,2,4,3,1,5,1,3,1,4,5,5,3,5,1,3,5,5,4,2,3,2,4,1,3,2,2,2,1,3,4,2,5,2,5,3,5,5,1,1,1,2,2,3,1,4,4,4,5,4,5,5,1,4,5,5,4,1,1,5,3,3,1,4,1,3,1,1,4,1,5,2,3,2,3,1,2,2,2,1,1,5,1,4,5,2,4,2,2,3};
    int pocet_dni_k_simulaci = 256;
    long long ryby_pole[9]={0};

    for(int ryba:ryby){
        ryby_pole[ryba]++;
    }
    zobraz_pole(ryby_pole);


    for(int i=0;i<pocet_dni_k_simulaci;i++){
        posun(ryby_pole);
        ryby_pole[6]+=ryby_pole[8];
        // zobraz_pole(ryby_pole);
    }
    std::cout<<suma(ryby_pole);
    
    return 0;
}