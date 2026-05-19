#include <iostream>
#include <string>
#include <vector>

class Ship
{
private:
    int north;
    int east;
    char direction;

    void rotate(char direction, int value);
    void move(int value);
    void move(char direction, int value);

public:
    Ship(int north, int east, char direction){
        this->north = north;
        this->east = east;
        this->direction = direction;
    }
    void navigate(std::vector<std::string> commands);
    void info();
};

int main()
{
    Ship lod1(0,0,'E');
    std::vector<std::string> instructions = {"F10",  "N3",  "F7", "R90",  "F11",
                                 "L180", "S4",  "E2", "R270", "F5",
                                 "W3",   "L90", "F8", "N1",   "F2"};

    lod1.navigate(instructions);
    lod1.info();
    // lod1.info();
    // lod1.move();
    // std::string input = "S10";
    // char command = input[0];
    // int value = stoi(input.substr(1));
    // std::cout<<command<<", "<<value<<std::endl;

    // lod1.navigate(command, value);
    // lod1.navigate('W', 15);
    // lod1.info();
    return 0;
}

void Ship::rotate(char direction, int value)
{
    std::string  directions = "NESW";
    int dir_index = directions.find(this->direction);
    int dir =  (direction=='L') ? 4-(value/90) : value/90;
    
    this->direction = directions[(dir+dir_index)%4];
}

void Ship::move(int value)
{
    move(direction, value);
}

void Ship::move(char direction, int value)
{
    switch (direction)
    {
    case 'N':
        north+=value;
        break;
    case 'S':
        north-=value;
        break;
    case 'E':
        east+=value;
        break;
    case 'W':
        east-=value;
        break;
    default:
        break;
    }
}

void Ship::navigate(std::vector<std::string> commands)
{
    for(std::string command: commands){
        char com = command[0];
        int value = stoi(command.substr(1));
        if(com == 'F'){
        move(value);
        }else if (com == 'R' || com =='L')
        {
            rotate(com, value);
        }else{
            move(com, value);
    }
    }
    
    
}

void Ship::info()
{
    std::cout<<north<<", "<<east<<", "<< direction<<", "<<abs(north)+abs(east)<<std::endl;
}
