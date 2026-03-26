

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> globalDirections;
std::vector<int> globalValues;

void loadNavigationData(std::string filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::string dir;
  int val;
  while (file >> dir >> val) {
    globalDirections.push_back(dir);
    globalValues.push_back(val);
  }

  file.close();
}

long long solveTask2Part1() {
  long long horizontal = 0;
  long long depth = 0;

  for (int i = 0; i < globalDirections.size(); i = i + 1) {
    std::string dir = globalDirections[i];
    int val = globalValues[i];

    if (dir == "forward") {
      horizontal = horizontal + val;
    } else if (dir == "down") {
      depth = depth + val;
    } else if (dir == "up") {
      depth = depth - val;
    }
  }

  return horizontal * depth;
}

long long solveTask2Part2() {
  long long horizontal = 0;
  long long depth = 0;
  long long aim = 0;

  for (int i = 0; i < globalDirections.size(); i = i + 1) {
    std::string dir = globalDirections[i];
    int val = globalValues[i];

    if (dir == "forward") {
      horizontal = horizontal + val;
      depth = depth + (aim * val);
    } else if (dir == "down") {
      aim = aim + val;
    } else if (dir == "up") {
      aim = aim - val;
    }
  }

  return horizontal * depth;
}

int main() {
  std::string filename = "2021_2.txt";
  loadNavigationData(filename);

  if (globalDirections.empty()) {
    std::cout << "No data loaded." << std::endl;
    return 1;
  }

  long long part1 = solveTask2Part1();
  long long part2 = solveTask2Part2();

  std::cout << "Task 2 (Global Variables) - Part 1: " << part1 << std::endl;
  std::cout << "Task 2 (Global Variables) - Part 2: " << part2 << std::endl;

  return 0;
}
