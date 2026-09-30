#include <iostream>

class Obdelnik{
    private: 
        int a = 10;
        int b = 12;
        int obvod(){
            return 2*a+2*b;
        }
        int obsah(){
            return a*b;
        }
    public:
        void tisk(){
            std::cout<<"Strana a: "<<a<<", strana b: "<<b<<
            ", obsah: "<<obsah()<<", obvod: "<<obvod()<<std::endl;
        }
        void zmen_a(int a){
            this->a=a;
        }
        void zmen_b(int b){
            this->b = b;
        }
        Obdelnik(int a, int b){
            this->a = a;
            this->b = b;
            std::cout<<"Obdelnik vytvoren"<<std::endl;
        }
        Obdelnik(){

        }
        ~Obdelnik(){
            std::cout<<"Obdelnik smazan."<<std::endl;
        }
};


int main(){

    Obdelnik obdelnik1(10,15);
    Obdelnik* pobdelnik1 = &obdelnik1;

    obdelnik1.tisk();
    obdelnik1.zmen_a(5);
    obdelnik1.zmen_b(8);
    pobdelnik1->tisk();


    return 0;
}