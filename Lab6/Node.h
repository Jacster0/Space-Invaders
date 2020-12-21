#pragma once

class Node {
public:
    int getData() const noexcept { return data; }
    void setData(int data) noexcept { this->data = data; }

    Node* getNext() const noexcept { return next; };
    void setNext(Node* next) noexcept { this->next = next; }

    Node* getPrev() const noexcept { return prev; }
    void setPrev(Node* prev) noexcept { this->prev = prev; }
private:
    int data;
    Node* next{ nullptr };
    Node* prev{ nullptr };
};