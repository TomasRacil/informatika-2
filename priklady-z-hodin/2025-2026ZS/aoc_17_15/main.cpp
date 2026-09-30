// #include <iostream>
// #include <fstream>
// #include <string>

// void nacti_startovni_hodnoty(std::string soubor,int* hodnota_a, int* hodnota_b) {
//     std::ifstream vstup(soubor);
//     if (!vstup.is_open()) {
//         std::cerr << "Chyba pri otevirani souboru." << std::endl;
//         return;
//     }
//     std::string radek;
//     std::getline(vstup, radek);
//     std::string hodnota_a_str, hodnota_b_str;
//     for (char c : radek) {
//         if (std::isdigit(c)) {
//             hodnota_a_str += c;
//         }
//     }

//     std::getline(vstup, radek);
//     for (char c : radek) {
//         if (std::isdigit(c)) {
//             hodnota_b_str += c;
//         }
//     }
//     vstup.close();
//     *hodnota_a = std::stoi(hodnota_a_str);
//     *hodnota_b = std::stoi(hodnota_b_str);
// }

// long long generation_step(long long previous_value, long long factor, long long divisor) {
//     return (previous_value * factor) % divisor;
// }

// void generate_values(int start_value, long long factor, long long divisor, int count, long long* values, int criteria = 1) {
//     long long current_value = start_value;
//     for (int i = 0; i < count; ++i) {
//         do {
//             current_value = generation_step(current_value, factor, divisor);
//         } while (current_value % criteria != 0);
//         values[i] = current_value;
//     }
// }

// int compare_lower_16_bits(long long value_a, long long value_b) {
//     return (value_a & 0xFFFF) == (value_b & 0xFFFF);
// }

// int compare_all_values(long long* value_a, long long* value_b, int count) {
//     int match_count = 0;
//     for (int i = 0; i < count; ++i) {
//         if (compare_lower_16_bits(value_a[i], value_b[i])) {
//             match_count++;
//         }
//     }
//     return match_count;
// }

// int main() {
//     int hodnota_a_str, hodnota_b_str;
//     // nacti_startovni_hodnoty("test.txt", &hodnota_a_str, &hodnota_b_str); // Pro testovani s testovacim souborem
//     nacti_startovni_hodnoty("data.txt", &hodnota_a_str, &hodnota_b_str);
//     std::cout << "Hodnota A: " << hodnota_a_str << std::endl;
//     std::cout << "Hodnota B: " << hodnota_b_str << std::endl;

//     const long long factor_a = 16807;
//     const long long factor_b = 48271;
//     const long long divisor = 2147483647;
//     // const int total_values = 5;  // Pro testovani s malym poctem hodnot
//     int total_values = 40000000;

//     long long* values_a = new long long[total_values];
//     long long* values_b = new long long[total_values];

//     generate_values(hodnota_a_str, factor_a, divisor, total_values, values_a);
//     generate_values(hodnota_b_str, factor_b, divisor, total_values, values_b);

//     // for (int i = 0; i < total_values; ++i) {
//     //     std::cout << "Value A[" << i << "]: " << values_a[i] << ", Value B[" << i << "]: " << values_b[i] << std::endl;
//     // }
//     int matches = compare_all_values(values_a, values_b, total_values);
//     std::cout << "Pocet shodnych hodnot v dolnich 16 bitech: " << matches << std::endl; 

//     total_values = 5000000;
//     generate_values(hodnota_a_str, factor_a, divisor, total_values, values_a, 4);
//     generate_values(hodnota_b_str, factor_b, divisor, total_values, values_b, 8);
//     matches = compare_all_values(values_a, values_b, total_values);
//     std::cout << "Pocet shodnych hodnot v dolnich 16 bitech (s kriterii): " << matches << std::endl;

//     return 0;
// }