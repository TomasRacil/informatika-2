#pragma once
#include "Node.h"

// DoubleNode dědí z Node a přidává ukazatel na předchozí prvek
template <typename T>
class DoubleNode : public Node<T> {
private:
    Node<T>* prev; // Ukazatel na předchozí uzel (typově Node<T>*, ale bude to DoubleNode)

public:
    DoubleNode(T newData) : Node<T>(newData), prev(nullptr) {}

    Node<T>* get_prev() { return prev; }
    
    void set_prev(Node<T>* prevNode) { this->prev = prevNode; }
};