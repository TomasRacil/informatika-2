#include <iostream>

int main() {

    std::cout<< "Zadejte vysku koruny stromu: ";
    int vyska;
    std::cin >> vyska;

    std::cout << "Zadejte sirku kmene stromu: ";
    int sirka;
    std::cin >> sirka;

    std::cout << "Zadejte vysku kmene stromu: ";
    int vyska_kmene;
    std::cin >> vyska_kmene;

    for (int i = 0; i < vyska; ++i) {
        for (int j = 0; j < vyska - i - 1; ++j) {
            std::cout << '-';
        }
        for (int k = 0; k < (2 * i + 1); ++k) {
            std::cout << '*';
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < vyska_kmene; ++i) {
        for (int j = 0; j < (vyska - sirka / 2 - 1); ++j) {
            std::cout << '-';
        }
        for (int k = 0; k < sirka; ++k) {
            std::cout << '#';
        }
        std::cout << std::endl;
    }
    return 0;
}