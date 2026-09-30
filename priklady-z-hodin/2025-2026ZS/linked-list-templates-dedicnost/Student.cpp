#include "Student.h"
#include <sstream>
#include <iomanip>

Student::Student(){
    id = 0;
    prumer = 0.0;
}

Student::Student(int id, std::string name, double prumer)
{
    this->id = id;
    this->name = name;
    this->prumer = prumer;
}

Student::Student(std::string radek){
    std::stringstream ss(radek);
    std::string idStr, nameStr, prumerStr;

    // Očekáváme formát: ID, Jméno, Průměr
    std::getline(ss, idStr, ',');
    std::getline(ss, nameStr, ',');
    std::getline(ss, prumerStr, ',');

    try {
        id = std::stoi(idStr);
        name = nameStr;
        prumer = std::stod(prumerStr);
    } catch (...) {
        // Pokud parsování selže (např. prázdný řádek), nastavíme výchozí hodnoty
        id = 0;
        name = "Unknown";
        prumer = 0.0;
    }
}

// Implementace porovnání pro třídění (třídíme podle průměru vzestupně)
bool Student::operator>(const Student& other) const {
    return this->prumer > other.prumer;
}

bool Student::operator<(const Student& other) const {
    return this->prumer < other.prumer;
}

std::ostream& operator<<(std::ostream& out, const Student& m){
    out << "ID: " << m.id << ", Jméno: " << m.name << ", Průměr: " << m.prumer;
    return out;
}