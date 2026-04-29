#include <iostream>

int main() {
  double teplota = 36.6;
  double &refTeplota = teplota;

  refTeplota = 37.7;

  std::cout << teplota << std::endl;

  int a = 10;
  int b = 20;
  int &ref = a;
  ref = b;
  std::cout << a << " " << b << std::endl;
}