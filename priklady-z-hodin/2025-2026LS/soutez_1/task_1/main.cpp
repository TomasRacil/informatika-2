#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> loadDepthData(std::string filename) {
  std::vector<int> data;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return data;
  }

  int value;
  while (file >> value) {
    data.push_back(value);
  }

  file.close();
  return data;
}

int solveTask1Part1(std::vector<int> data) {
  int count = 0;

  if (data.empty()) {
    return 0;
  }

  for (int i = 1; i < data.size(); i = i + 1) {
    if (data[i] > data[i - 1]) {
      count = count + 1;
    }
  }

  return count;
}

int solveTask1Part2(std::vector<int> data) {
  int count = 0;

  if (data.size() < 4) {
    return 0;
  }

  for (int i = 3; i < data.size(); i = i + 1) {
    int windowA = data[i - 3] + data[i - 2] + data[i - 1];
    int windowB = data[i - 2] + data[i - 1] + data[i];

    if (windowB > windowA) {
      count = count + 1;
    }
  }

  return count;
}

int main() {
  std::string filename = "2021_1.txt";
  std::vector<int> data = loadDepthData(filename);

  if (data.empty()) {
    std::cout << "No data loaded." << std::endl;
    return 1;
  }

  int part1 = solveTask1Part1(data);
  int part2 = solveTask1Part2(data);

  std::cout << "Task 1 - Part 1: " << part1 << std::endl;
  std::cout << "Task 1 - Part 2: " << part2 << std::endl;

  return 0;
}