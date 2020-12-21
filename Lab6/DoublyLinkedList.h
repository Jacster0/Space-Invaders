#pragma once
#include "Node.h"

class DoublyLinkedList {
public:
    bool add(Node* data, int pos);
    bool remove(int pos);
    bool replace(Node* oldNode, Node* newNode);
    int search(Node* data);
    Node* nodeAt(int pos);
    void display_forward();
    void display_backward();
    int size();
private:
    Node* head;
    Node* tail;
    int size;
};