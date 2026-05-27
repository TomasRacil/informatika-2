// 1. Šablona funkce
// Vytvořte šablonu funkce vymen(T& a, T& b), která prohodí hodnoty dvou proměnných libovolného typu. Vyzkoušejte pro int, double a string.

// 2. Šablona třídy
// Napište šablonovou třídu Schranka<T>, která bude uchovávat jednu hodnotu typu T.

// Metodu vloz(T data)
// Metodu T vyzvedni() Vyzkoušejte pro různá data.
#include <iostream>

template<typename T>
void vymen(T& a, T& b){
    T pomcna = b;
    b=a;
    a=pomcna;
}


int main(){
    int a = 2;
    int b = 3;

    double d1= 3.5;
    double d2= 4.2;

    std::string s1 = "Ahoj";
    std::string s2 = "Nashle";

    std::cout<<a<<":"<<b<<std::endl;
    vymen(a,b);
    std::cout<<a<<":"<<b<<std::endl;

    std::cout<<d1<<":"<<d2<<std::endl;
    vymen(d1,d2);
    std::cout<<d1<<":"<<d2<<std::endl;

    std::cout<<s1<<":"<<s2<<std::endl;
    vymen(s1,s2);
    std::cout<<s1<<":"<<s2<<std::endl;

    return 0;
}