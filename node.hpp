#pragma once
#include <iostream>
using namespace std;

template <class T>
class Node {
private:
    Node<T>* next; // next pointer is private

public:
    T data; // data is public

    // Constructor
    Node(const T &item, Node<T> *ptrNext = NULL);
    // Member functions
    void insert_after(Node<T> *mptr);
    Node<T>* delete_after();
    Node<T>* NextNode() const;
};

// Constructor definition
template <class T>
Node<T>::Node(const T &item, Node<T> *ptrnext) : data(item), next(ptrnext) {}

// Insert a node after the current node
template <class T>
void Node<T>::insert_after(Node<T> *mptr) {
    if (mptr != NULL) {
        mptr->next = next;
        next = mptr;
    }
}

// Delete the node after the current node
template <class T>
Node<T>* Node<T>::delete_after() {
    Node<T>* tempPtr = next;
    if (next == NULL) {
        return NULL;
    }
    next = tempPtr->next;
    return tempPtr;
}

// Return the next node
template <class T>
Node<T>* Node<T>::NextNode() const {
    return next;
}
