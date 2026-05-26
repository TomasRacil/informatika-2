#include <iostream>

using namespace std;

class Person {
private:
    string jmeno;
public:
    Person(string jmeno) { // Konstruktor základní třídy
        this->jmeno = jmeno;
    }
    string get_jmeno(){
        return jmeno;
    }
};

class Student : public Person {
private:
    string skola;
public:
    // 'Person(jmeno)' je volání konstruktoru základní třídy
    Student(string jmeno, string skola) : Person(jmeno) {
        this->skola = skola;
    }
    void vypis_info(){
        cout<<get_jmeno()<<", "<<skola<<endl;
    }
};

int main(){

    Student s = Student("Josef", "Gymnazium");
    s.vypis_info();

    return 0;
}

