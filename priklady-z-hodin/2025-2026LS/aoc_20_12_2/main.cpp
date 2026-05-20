#include <iostream>
#include <string>
#include <vector>

class Waypoint
{
private:
    int north;
    int east;

public:
    Waypoint();
    Waypoint(int north, int east);
    int get_north();
    int get_east();
    void move(char direction, int value);
    void rotate(char direction, int value);
};

Waypoint::Waypoint()
{
   this->north = 0;
    this->east = 0; 
}

Waypoint::Waypoint(int north, int east)
{
    this->north = north;
    this->east = east;
}

int Waypoint::get_north()
{
    return north;
}

int Waypoint::get_east()
{
    return east;
}

void Waypoint::move(char direction, int value)
{
    switch (direction)
    {
    case 'N':
        north += value;
        break;
    case 'S':
        north -= value;
        break;
    case 'E':
        east += value;
        break;
    case 'W':
        east -= value;
        break;
    default:
        break;
    }
}

void Waypoint::rotate(char direction, int value)
{
    if (direction == 'L')
        value = 360 - (value % 360);
    else
        value = value % 360;

    int tempEast = east;
    int tempNorth = north;

    if (value == 90)
    {
        east = tempNorth;
        north = -tempEast;
    }
    else if (value == 180)
    {
        east = -tempEast;
        north = -tempNorth;
    }
    else if (value == 270)
    {
        east = -tempNorth;
        north = tempEast;
    }
}

class Ship
{
private:
    int north;
    int east;
    Waypoint wp;

    void move(int value);

public:
    Ship(int north, int east, Waypoint wp)
    {
        this->north = north;
        this->east = east;
        this->wp = wp;
    }
    void navigate(std::vector<std::string> commands);
    void info();
};


void Ship::move(int value)
{
    north = north + value * wp.get_north();
    east = east + value * wp.get_east();
}

void Ship::navigate(std::vector<std::string> commands)
{
    for (std::string command : commands)
    {
        char com = command[0];
        int value = stoi(command.substr(1));
        if (com == 'F')
        {
            move(value);
        }
        else if (com == 'R' || com == 'L')
        {
            wp.rotate(com, value);
        }
        else
        {
            wp.move(com, value);
        }
    }
}

void Ship::info()
{
    std::cout << north << ", " << east << ", " << ", " << abs(north) + abs(east) << std::endl;
}

int main()
{
    Ship lod1(0, 0, Waypoint(1, 10));
    std::vector<std::string> instructions = {"F10", "N3", "F7", "R90", "F11",
                                             "L180", "S4", "E2", "R270", "F5",
                                             "W3", "L90", "F8", "N1", "F2"};

    lod1.navigate(instructions);
    lod1.info();
    return 0;
}

