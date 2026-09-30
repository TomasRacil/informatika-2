#include <vector>
#include <iostream>


void vypis_fib_trojuhelnik(int n){
    std::vector<std::vector<long long>> trojuhelnik(n);

    for (int i = 0; i < n; i++) {
        trojuhelnik[i].resize(i + 1);

        for (int mezera = 0; mezera < n - i - 1; mezera++) {
            std::cout << " ";
        }

        for (int j = 0; j <= i; j++) {
            
            if (j == 0 || j == i) {
                trojuhelnik[i][j] = 1;
            } else {
                trojuhelnik[i][j] = trojuhelnik[i - 1][j - 1] + trojuhelnik[i - 1][j];
            }
            std::cout << trojuhelnik[i][j] << " ";
        }
        
        std::cout << std::endl;
    }
}

int main(){
    int n;
    std::cout << "Zadejte pocet radku: ";
    std::cin >> n;
    vypis_fib_trojuhelnik(n);
    return 0;
}