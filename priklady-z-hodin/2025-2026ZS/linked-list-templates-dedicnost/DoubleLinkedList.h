#pragma once
#include "LinkedList.h"
#include "DoubleNode.h"

template <typename T>
class DoubleLinkedList : public LinkedList<T> {
public:
    // Překrytí metody přidání prvku
    void pridejPrvek(T newData) override {
        // Vytváříme DoubleNode místo obyčejného Node
        DoubleNode<T>* newNode = new DoubleNode<T>(newData);

        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            Node<T>* current = this->head;
            while (current->get_next() != nullptr) {
                current = current->get_next();
            }
            
            // Nastavení next u posledního prvku na nový
            current->set_next(newNode);
            
            // SPECIFICKÉ PRO DOUBLE LINKED LIST:
            // Nastavení prev u nového prvku na původní poslední
            newNode->set_prev(current);
        }
    }
};