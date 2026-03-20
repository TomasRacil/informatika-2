#include <iostream>

int main(){
    int vek=30;
    float vyska=180;
    char pismeno='t';
    bool student=false;

    std::cout
    <<vek<<"\n"
    <<vyska<<std::endl
    <<pismeno<<std::endl
    <<student<<"\n";


    int a,b;

    std::cin>>a;
    std::cin>>b;

    std::cout<<a<<"+"<<b<<"="<<a+b<<std::endl;
    std::cout<<a<<"*"<<b<<"="<<a*b<<std::endl;
    std::cout<<a<<"/"<<b<<"="<<a/b<<std::endl;
    std::cout<<a<<"-"<<b<<"="<<a-b<<std::endl;


    if(10<b && b<20){
        std::cout<<true<<std::endl;
    }

    return 0;
}