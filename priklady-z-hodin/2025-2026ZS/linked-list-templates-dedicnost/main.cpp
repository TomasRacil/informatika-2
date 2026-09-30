#include <iostream>
#include <string>
#include <fstream>
#include "LinkedList.h"
#include "DoubleLinkedList.h"
#include "Student.h"

using namespace std;

// Pomocná funkce pro načtení ze souboru do libovolného listu
template <typename ListType>
void nactiStudentyZeSouboru(ListType& list, const string& filename) {
    ifstream soubor(filename);
    string radek;

    if (!soubor.is_open()) {
        cerr << "Soubor se nepodařilo otevřít: " << filename << endl;
        return;
    }

    while (getline(soubor, radek)) {
        if (radek.find("#") != 0 && !radek.empty()) {
            Student st(radek);
            list.pridejPrvek(st);
        }
    }
    soubor.close();
}

int main() {
    string input_file = "studenti.txt";

    // 1. POUŽITÍ BĚŽNÉHO LINKED LISTU (Generický s typem Student)
    cout << "=== BĚŽNÝ LINKED LIST (Node) ===" << endl;
    LinkedList<Student> studentList;
    
    nactiStudentyZeSouboru(studentList, input_file);

    cout << "\nPred serazenim:" << endl;
    cout << studentList;

    studentList.setridSeznam();

    cout << "\nPo serazeni (podle prumeru):" << endl;
    cout << studentList;

    
    // 2. POUŽITÍ DOUBLE LINKED LISTU (Dědí z LinkedList)
    cout << "\n\n=== DOUBLE LINKED LIST (DoubleNode) ===" << endl;
    DoubleLinkedList<Student> doubleList;

    doubleList.pridejPrvek(Student(999, "Jan Novy (DLL)", 1.0));
    doubleList.pridejPrvek(Student(888, "Petr Stary (DLL)", 3.5));
    doubleList.pridejPrvek(Student(777, "Alena Dvojita (DLL)", 2.0));

    cout << "\nNormální výpis:" << endl;
    // Funguje i pro DoubleLinkedList, protože dědí z LinkedList
    cout << doubleList;

    doubleList.setridSeznam();
    cout << "\nPo setřídění:" << endl;
    cout << doubleList;

    // 3. DEMONSTRACE GENERIČNOSTI (List integerů)
    cout << "\n\n=== GENERICKÝ TEST (List<int>) ===" << endl;
    LinkedList<int> intList;
    intList.pridejPrvek(5);
    intList.pridejPrvek(1);
    intList.pridejPrvek(4);
    intList.pridejPrvek(2);
    
    cout << "Inty pred serazenim:\n";
    cout << intList;
    
    intList.setridSeznam();
    
    cout << "Inty po serazeni:\n";
    cout << intList;

    return 0;
}