#pragma once
#include <iostream>
#include "Node.h"

// Předdeklarace šablony třídy a operátoru
template <typename T> class LinkedList;
template <typename T> std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list);

template <typename T>
class LinkedList {
protected:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    virtual ~LinkedList() {
        vycistiSeznam();
    }

    void vycistiSeznam() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->get_next();
            delete current;
            current = next;
        }
        head = nullptr;
    }

    virtual void pridejPrvek(T newData) {
        Node<T>* newNode = new Node<T>(newData);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->get_next() != nullptr) {
                current = current->get_next();
            }
            current->set_next(newNode);
        }
    }
    
    // Generické třídění (Bubble Sort)
    void setridSeznam() {
        if (head == nullptr || head->get_next() == nullptr) return;

        bool swapped;
        Node<T>* ptr1;
        Node<T>* lptr = nullptr;

        do {
            swapped = false;
            ptr1 = head;

            while (ptr1->get_next() != lptr) {
                if (ptr1->get_data() > ptr1->get_next()->get_data()) {
                    T temp = ptr1->get_data();
                    ptr1->set_data(ptr1->get_next()->get_data());
                    ptr1->get_next()->set_data(temp);
                    swapped = true;
                }
                ptr1 = ptr1->get_next();
            }
            lptr = ptr1;
        } while (swapped);
    }
    
    Node<T>* getHead() const { return head; }

    // Friend deklarace pro operátor <<
    friend std::ostream& operator<< <>(std::ostream& out, const LinkedList<T>& list);
};

// Implementace operátoru << mimo třídu
template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list) {
    Node<T>* current = list.head;
    while (current != nullptr) {
        // Vypíšeme data uzlu (využívá operator<< z třídy Node, pokud existuje, nebo přímo datový typ)
        // Přidáme konec řádku pro každý prvek, aby to vypadalo jako seznam
        out << *current << ", ";
        current = current->get_next();
    }
    out << std::endl;
    return out;
}