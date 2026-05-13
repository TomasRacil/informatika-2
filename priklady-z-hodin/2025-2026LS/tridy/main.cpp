#include <iostream>

class Auto
{
private:
    std::string znacka;
    int rokVyroby;
public:
  Auto();
  Auto(std::string znacka, int rokVyroby);
  void nastavHodnoty(std::string znacka, int rokVyroby);
  void vypisInfo(){
    std::cout<<"Vozidlo se znackou: "<<znacka<<" a rokem vyroby: " <<rokVyroby<<std::endl;
  }
  ~Auto();
};

int main(){

    Auto auto1("Skoda",2010);
    {
        Auto auto2("Fiat",2005);
    }

    auto1.vypisInfo();
    auto1.nastavHodnoty("Ford", 2015);
    auto1.vypisInfo();


    return 0;
}

Auto::Auto()
{
    this->znacka="";
    this->rokVyroby=0;
}

Auto::Auto(std::string znacka, int rokVyroby)
{
    this->znacka=znacka;
    this->rokVyroby = rokVyroby;
}

void Auto::nastavHodnoty(std::string znacka, int rokVyroby)
{
    this->znacka=znacka;
    this->rokVyroby = rokVyroby;
}

Auto::~Auto()
{
    std::cout<<znacka<<" s rokem vyroby "<<rokVyroby<<" smazana"<<std::endl;
}
