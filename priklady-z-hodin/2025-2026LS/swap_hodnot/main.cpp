#include <iostream>

// ÚKOL 1: Doplňte prohození hodnot pomocí pointrů
void swapPointer(int *a, int *b) {
  // int temp = *a;
  // *a = *b;
  // *b = temp;
  *a = *a + *b;
  *b = *a - *b;
  *a = *a - *b;
}

// ÚKOL 2: Doplňte prohození hodnot pomocí referencí
void swapReference(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  int x = 10, y = 20;
  std::cout << "Puvodni: x=" << x << ", y=" << y << "\n";

  // Volání pointer verze (nezapomeňte poslat adresy!)
  swapPointer(&x, &y);
  std::cout << "Po swapPointer: x=" << x << ", y=" << y << "\n";

  // Volání referenční verze
  swapReference(x, y);
  std::cout << "Po swapReference: x=" << x << ", y=" << y << "\n";

  return 0;
}