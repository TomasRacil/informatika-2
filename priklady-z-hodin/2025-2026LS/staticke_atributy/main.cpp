#include <iostream>

class Player
{
private:
    /* data */
public:
    static int pocetHracu;
    Player(/* args */);
    static int getPocetHracu();
    ~Player();
};

Player::Player(/* args */)
{
    pocetHracu++;
}

int Player::getPocetHracu()
{
    return pocetHracu;
}

Player::~Player()
{
    pocetHracu--;
}

int Player::pocetHracu = 0;


int main(){
    Player p1;
    {
        std::cout<<Player::getPocetHracu()<<std::endl;
        Player p2;
        {
            std::cout<<Player::getPocetHracu()<<std::endl;
            Player p3;
            std::cout<<Player::getPocetHracu()<<std::endl;
        }
        std::cout<<Player::getPocetHracu()<<std::endl;
    }
    std::cout<<Player::getPocetHracu()<<std::endl;


}