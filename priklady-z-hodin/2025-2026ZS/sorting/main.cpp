#include <iostream>
#include <ctime>
#include <chrono>

void prohod(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int* pole, int velikost){
    for(int i = 0; i< velikost; i++){
        int min_idx = i;
        for(int j = i+1; j<velikost; j++){
            if (pole[j]<pole[min_idx]){
                min_idx = j;
            }
        }
        prohod(&pole[min_idx], &pole[i]);
    }
}

int partition(int pole[], int low, int high) {
    int pivot = pole[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (pole[j] < pivot) {
            i++;
            prohod(&pole[i], &pole[j]);
        }
    }
    prohod(&pole[i + 1], &pole[high]);
    return (i + 1);
}

void quick_sort(int* pole, int low, int high) {
    if (low < high) {
        int pi = partition(pole, low, high);
        quick_sort(pole, low, pi - 1);
        quick_sort(pole, pi + 1, high);
    }
}

void tridici_funkce(int* pole, int velikost, std::string algoritmus){
    if(algoritmus=="selection"){
        selection_sort(pole, velikost);
    }else if (algoritmus=="quick")
    {
        quick_sort(pole, 0, velikost-1);
    }
    
}

void vypis_pole(int* pole, int velikost, int n = 10) {
    std::cout << "[";
    for (int i = 0; i < velikost && i < n; ++i) {
        std::cout << pole[i] << (i == velikost - 1 || i == n - 1 ? "" : ", ");
    }
    if (velikost > n) {
        std::cout << "...";
    }
    std::cout << "]" << std::endl;
}

int main(){
    std::cout<<"Zadejte pocet generovanych cisel: ";
    int n;
    std::cin>>n;
    std::srand(std::time(0));
    int* pole = new int[n];
    for (int i = 0; i < n; ++i){
        pole[i] = std::rand();
    }
    vypis_pole(pole, n);

    auto start = std::chrono::high_resolution_clock::now();
    // tridici_funkce(pole, n, "selection");
    tridici_funkce(pole, n, "quick");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Algoritmus trval: " << duration.count() << " ms" << std::endl;

    vypis_pole(pole, n);

    return 0;
}