#include "DoublyLinkedList.h"
#include <iostream>

DoublyLinkedList::DoublyLinkedList() try {
    head = new Node;
    tail = new Node;

    head->setNext(tail);
    head->setPrev(nullptr);

    tail->setNext(nullptr);
    tail->setPrev(head);

    head->setData(-1);
    tail->setData(-1);
    
}

catch(...) {
    delete head;
    delete tail;
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* node = head;
    int i = 0;

    while (i++ != length +2) {
        Node* old = node;
        if (node) {
            node = node->getNext();
        }
        delete old;
    }
}

bool DoublyLinkedList::add(Node* data, int pos) noexcept {
    if (!data)
        return false;
    if (!head || !tail)
        return false;
    //special case when the list is empty
    if (pos == 0 && length == 0) {
        data->setNext(head->getNext());
        data->setPrev(head);

        head->setNext(data);
        tail->setPrev(data);

        length++;

        return true;
    }

    if (pos < 0 || pos >= length + 1) {
        return false;
    }

    if (Node* current = nodeAt(pos)) {
        data->setNext(current);
        data->setPrev(current->getPrev());

        current->getPrev()->setNext(data);
        current->setPrev(data);

        length++;
        return true;
    }
    return false;
}

bool DoublyLinkedList::remove(int pos) noexcept {
    if (Node* nodeToBeRemoved = nodeAt(pos)) {
        nodeToBeRemoved->getPrev()->setNext(nodeToBeRemoved->getNext());
        nodeToBeRemoved->getNext()->setPrev(nodeToBeRemoved->getPrev());

        nodeToBeRemoved->setNext(nullptr);
        nodeToBeRemoved->setPrev(nullptr);

        delete nodeToBeRemoved;
        nodeToBeRemoved = nullptr;

        length--;
        return true;
    }
    return false;
}

bool DoublyLinkedList::replace(Node* oldNode, Node* newNode) noexcept {
    if (oldNode && newNode) {
        if (oldNode->getNext() && oldNode->getPrev()) {
            auto index = search(oldNode);
            if (index != -1) {
                Node* node = newNode;
                //If the newNode already exists in the list, the list will have the newNode point
                //to it self, which will cause the display methods to enter an infinite loop.
                //to solve this we create a entirely new node and just copy the newNode's data 
                if (search(newNode) != -1) {
                    node = new Node;
                    node->setData(newNode->getData());
                }
                add(node, index);
                remove(index+1);
                
                return true;
            }
        }
        return false;
    }
    return false;
}

int DoublyLinkedList::search(Node* data) noexcept {
    for (int i = 0; i < length; i++) {
        if (Node* node = nodeAt(i)) {
            if (node == data) {
                return i;
            }
        }
    }
    return -1;
}

Node* DoublyLinkedList::nodeAt(int pos) noexcept {
    if (!head)
        return nullptr;
    Node* node = head->getNext();

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
        if (node == head) {
            node = node->getNext();
            continue;
        }

        else if (node == tail) {
            break;
        }

        std::cout << node->getData() << " ";
        node = node->getNext();
    }
    std::cout << std::endl;
}

void DoublyLinkedList::display_backward() const noexcept {
    Node* node = tail;

    while (node != nullptr) {
        if (node == tail) {
            node = node->getPrev();
            continue;
        }

        else if (node == head) {
            break;
        }
        std::cout << node->getData() << " ";
        node = node->getPrev();
    }

    std::cout << std::endl;
}

int DoublyLinkedList::size() const noexcept {
    return length;
}