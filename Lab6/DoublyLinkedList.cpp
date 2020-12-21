#include "DoublyLinkedList.h"
#include <iostream>

DoublyLinkedList::DoublyLinkedList() noexcept {
    head = new(std::nothrow) Node;
    tail = new(std::nothrow) Node;

    if (head && tail) {
        head->setNext(tail);
        head->setPrev(nullptr);
        head->setData(0);

        tail->setNext(nullptr);
        tail->setPrev(head);
        tail->setData(0);

        length = 2;
    }
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* node = head;
    int i = 0;

    while (i++ != length) {
        Node* old = node;
        node = node->getNext();
        delete old;
    }
}

bool DoublyLinkedList::add(Node* data, int pos) noexcept {
    if (!data || pos < 0 || pos >= length) {
        return false;
    }

    else {
        Node* node = nodeAt(pos);
        Node* next = nullptr;

        if (node) {
            next = node->getNext();

            data->setNext(next);
            node->setNext(data);

            data->setPrev(node);

            //if next is nullptr means that data is the new tail node and thus
            //we cannot call next->setPrev(data)
            if (next) {
                next->setPrev(data);
            }

            length++;

            return true;
        }

        return false;
    }
}

bool DoublyLinkedList::remove(int pos) noexcept {
    
    if(Node* node = nodeAt(pos)) {
        Node* next = node->getNext();
        Node* prev = node->getPrev(); 

        //node is neither head or tail
        if (next && prev) {
            prev->setNext(next);
            next->setPrev(prev);
        }

        //our node is the head
        if (next && !prev) {
            next->setPrev(nullptr);
        }

        //our node is the tail
        else if (prev && !next) {
            prev->setNext(nullptr);
        }

        --length;
        delete node;
        node = nullptr;

        return true;
    }
    return false;
}


//TODO: make this exception safe 
bool DoublyLinkedList::replace(Node* oldNode, Node* newNode) noexcept {

    if (oldNode && newNode) {
        Node* oldNext = oldNode->getNext();
        Node* oldPrev = oldNode->getPrev();

        newNode->setNext(oldNext);
        newNode->setPrev(oldPrev);

        //old node is neither head or tail 
        if (oldNext && oldPrev) {
            oldNext->setPrev(newNode);
            oldPrev->setNext(newNode);
        }

        //old node is head
        if (oldNext && !oldPrev) {
            oldNext->setPrev(newNode);
        }

        //old node is head
        if (oldPrev && !oldNext) {
            oldPrev->setNext(newNode);
        }

        delete oldNode;
        oldNode = nullptr;

        return true; 
    }
    
    return false;
}

int DoublyLinkedList::search(Node* data) noexcept {
    for (int i = 0; i < length; i++) {
        Node* node = nodeAt(i);

        if (node->getData() == data->getData()) {
            return i;
        }
    }
    return -1;
}

Node* DoublyLinkedList::nodeAt(int pos) noexcept {
    Node* node = head;
    int i = 0;

    if (pos < 0 || pos >= length) {
        return nullptr;
    }

    while (node != nullptr) {
        if (i++ == pos) {
            return node;
        }
        node = node->getNext();
    }
    
    return nullptr;
}

void DoublyLinkedList::display_forward() const noexcept {
    Node* node = head;

    while (node != nullptr) {
        std::cout << node->getData() << std::endl;
        node = node->getNext();
    }
}

void DoublyLinkedList::display_backward() const noexcept {
    Node* node = tail;

    while (node != nullptr) {
        std::cout << node->getData() << std::endl;
        node = node->getPrev();
    }
}

int DoublyLinkedList::size() const noexcept {
    return length;
}
