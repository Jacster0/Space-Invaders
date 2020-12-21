#pragma once
#include "Node.h"

class DoublyLinkedList {
public:
    DoublyLinkedList() noexcept;
    ~DoublyLinkedList();

    bool add(Node* data, int pos) noexcept;
    bool remove(int pos) noexcept;
    bool replace(Node* oldNode, Node* newNode) noexcept;
    int search(Node* data) noexcept;
    Node* nodeAt(int pos) noexcept;
    void display_forward() const noexcept;
    void display_backward() const noexcept;
    int size() const noexcept;
private:
    Node* head;
    Node* tail;
    int length{ 0 };
};