#pragma once
#include <iostream>

// Třída Node je nyní šablona typu T
template <typename T>
class Node {
protected:
    T data;
    Node<T>* next;

public:
    Node() : next(nullptr) {}
    
    Node(T newData) : data(newData), next(nullptr) {}
    
    // Virtuální destruktor je důležitý pro dědičnost
    virtual ~Node() {}

    Node<T>* get_next() { return next; }
    
    T& get_data() { return data; } // Vracíme referenci, abychom mohli data měnit (swap)
    
    void set_next(Node<T>* nextNode) { this->next = nextNode; }
    
    void set_data(T newData) { this->data = newData; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, Node<U>& m);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, Node<T>& m){
    out << m.data;
    return out;
}