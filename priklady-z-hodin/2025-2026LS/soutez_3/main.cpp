#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Pomocna trida pro waypoint
class Waypoint {
public:
  int x; // Relativni x vuci lodi
  int y; // Relativni y vuci lodi

  Waypoint(int startX, int startY) : x(startX), y(startY) {}

  void move(char direction, int value) {
    if (direction == 'N')
      y += value;
    else if (direction == 'S')
      y -= value;
    else if (direction == 'E')
      x += value;
    else if (direction == 'W')
      x -= value;
  }

  void rotate(char direction, int degrees) {
    if (direction == 'L')
      degrees = 360 - (degrees % 360);
    else
      degrees = degrees % 360;

    int tempX = x;
    int tempY = y;

    if (degrees == 90) {
      x = tempY;
      y = -tempX;
    } else if (degrees == 180) {
      x = -tempX;
      y = -tempY;
    } else if (degrees == 270) {
      x = -tempY;
      y = tempX;
    }
  }
};

// 1. Lod pro prime rizeni (Cast A)
class DirectShip {
private:
  int x = 0;
  int y = 0;
  char direction = 'E'; // 'N'=Sever, 'E'=Vychod, 'S'=Jih, 'W'=Zapad

  // Posun lodi v zadanem svetovem smeru
  void move(char direction, int value) {
    if (direction == 'N')
      y += value;
    else if (direction == 'S')
      y -= value;
    else if (direction == 'E')
      x += value;
    else if (direction == 'W')
      x -= value;
  }

  // Otoceni lodi
  void rotate(char turn, int value) {
    int steps = value / 90;
    if (turn == 'L') {
      steps = 4 - (steps % 4);
    }
    string dirs = "NESW";
    int currentIndex = dirs.find(direction);
    direction = dirs[(currentIndex + steps) % 4];
  }

  // Posun lodi dopredu v aktualnim smeru lodi
  void move(int value) { move(direction, value); }

public:
  void processInstructions(const vector<string> &instructions) {
    for (const string &instr : instructions) {
      char action = instr[0];
      int value = stoi(instr.substr(1));

      if (action == 'N' || action == 'S' || action == 'E' || action == 'W') {
        move(action, value);
      } else if (action == 'L' || action == 'R') {
        rotate(action, value);
      } else if (action == 'F') {
        move(value);
      }
    }
  }

  int getManhattanDistance() const { return abs(x) + abs(y); }
};

// 2. Lod rizena pomoci Waypointu (Cast B)
class WaypointShip {
private:
  int shipX = 0;
  int shipY = 0;
  Waypoint wp;

  // Posun waypointu v zadanem svetovem smeru
  void move(char direction, int value) { wp.move(direction, value); }

  // Otoceni waypointu
  void rotate(char direction, int value) { wp.rotate(direction, value); }

  // Posun lodi dopredu smerem k waypointu
  void move(int value) {
    shipX += wp.x * value;
    shipY += wp.y * value;
  }

public:
  WaypointShip() : wp(10, 1) {}

  void processInstructions(const vector<string> &instructions) {
    for (const string &instr : instructions) {
      char action = instr[0];
      int value = stoi(instr.substr(1));

      if (action == 'N' || action == 'S' || action == 'E' || action == 'W') {
        move(action, value);
      } else if (action == 'L' || action == 'R') {
        rotate(action, value);
      } else if (action == 'F') {
        move(value);
      }
    }
  }

  int getManhattanDistance() const { return abs(shipX) + abs(shipY); }
};

int main() {
  vector<string> instructions = {"F10",  "N3",  "F7", "R90",  "F11",
                                 "L180", "S4",  "E2", "R270", "F5",
                                 "W3",   "L90", "F8", "N1",   "F2"};

  DirectShip shipA;
  shipA.processInstructions(instructions);
  cout << "Rezim A (Prime rizeni) - Manhattanska vzdalenost: "
       << shipA.getManhattanDistance() << " (Ocekavano: 32)" << endl;

  WaypointShip shipB;
  shipB.processInstructions(instructions);
  cout << "Rezim B (Waypoint) - Manhattanska vzdalenost: "
       << shipB.getManhattanDistance() << " (Ocekavano: 374)" << endl;

  return 0;
}