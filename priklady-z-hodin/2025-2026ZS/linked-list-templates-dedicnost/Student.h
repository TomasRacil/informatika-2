#pragma once

#include <string>
#include <iostream>

struct Student
{
    int id;
    std::string name;
    double prumer;
    
    Student();
    Student(int id, std::string name, double prumer);
    Student(std::string radek);

    // Operátory pro porovnávání (potřebné pro třídění Generic Listu)
    bool operator>(const Student& other) const;
    bool operator<(const Student& other) const;
};

std::ostream& operator<<(std::ostream& out, const Student& m);