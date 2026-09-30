#include <string>
#include <fstream>
#include <iostream>

class Waypoint{
private:
    int x = 10;
    int y = 1;
public:
    friend std::ostream& operator<<(std::ostream& os, const Waypoint& w);
    Waypoint operator+(Waypoint smer){
        Waypoint result;
        result.x= this->x+smer.x;
        result.y = this->y+smer.y;
        return result;
    };
    void posun_smerem(char smer, int kroky)
    {
        switch (smer)
        {
        case 'N':
            y += kroky;
            break;
        case 'S':
            y -= kroky;
            break;
        case 'E':
            x += kroky;
            break;
        case 'W':
            x -= kroky;
            break;
        default:
            break;
        }
    }
    void otoc(char smer, int stupne)
    {
        if (stupne == 180)
        {
            x=-x;
            y=-y;
        }else if (stupne == 90 && smer=='L' || stupne == 270 && smer=='R')
        {
            int temp = x; 
            x = -y;
            y = temp;
        }else if (stupne == 270 && smer=='L' || stupne == 90 && smer=='R')
        {
            int temp = x; 
            x = y;
            y = -temp;
        }
        
        
        
    }
    int get_x(){
        return x;
    }
    int get_y(){
        return y;
    }
};

std::ostream& operator<<(std::ostream& os, const Waypoint& w) {
    os << "Waypoint(" << w.x << ", " << w.y << ")";
    return os; 
}

class Lod
{
private:
    int x = 0;
    int y = 0;
    Waypoint smer;
    std::string filename;
public:
    Lod(std::string filename)
    {
        this->filename = filename;
        smer = Waypoint();
    }
    void navigace()
    {
        std::string radek;
        std::ifstream soubor(filename);
        if (!soubor.is_open())
        {
            std::cerr << "Chyba: Soubor '" << filename << "' se nepodařilo otevřít!" << std::endl;
        }

        while (soubor >> radek)
        {
            if (!radek.empty())
            {
                std::cout<<radek<<std::endl;
                char prikaz = radek[0];
                int hodnota = std::stoi(radek.substr(1));
                if (prikaz == 'F')
                {
                    posun_dopredu(hodnota);
                }
                else if (prikaz == 'L' || prikaz == 'R')
                {
                    smer.otoc(prikaz, hodnota);
                }
                else
                {
                    smer.posun_smerem(prikaz, hodnota);
                }
            }
            vypis_pozici();
        }
        soubor.close();
    }
    void posun_dopredu(int kroky)
    {
        x+=(smer.get_x()*kroky);
        y+=(smer.get_y()*kroky);
    }
    void vypis_pozici()
    {
        std::cout << "Pozice x: " << x << ", pozice y: " << y <<", info o waypointu: " << smer<<", manhatnovska vzdalenost: " << abs(x) + abs(y) << std::endl;\
    }
};

int main()
{
    Lod lod("test.txt");
    lod.vypis_pozici();
    lod.navigace();
    // Waypoint w1;
    // Waypoint w2;
    // Waypoint r = w1 + w2;
    // std::cout<< r <<std::endl;
    // r=w1.operator+(w2);
    // r.vypis_pozici();

    
    return 0;
}