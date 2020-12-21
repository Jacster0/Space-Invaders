#include "DoublyLinkedList.h"

bool DoublyLinkedList::add(Node* data, int pos) {
    if (pos < 0 || pos >= size) {
        return false;
    }

    else {
        Node* node = nodeAt(pos);

        data->setNext(node->getNext());
        data->setPrev(node);

        node->setNext(data);
        size++;

        return true;
    }
}

bool DoublyLinkedList::remove(int pos) {
    Node* node = nodeAt(pos);

    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());

    --size;
    delete node;
   
    return true;
}

bool DoublyLinkedList::replace(Node* oldNode, Node* newNode) {
    newNode->setNext(oldNode->getNext());
    newNode->setPrev(oldNode->getPrev());
}

int DoublyLinkedList::search(Node* data)
{
    return 0;
}

Node* DoublyLinkedList::nodeAt(int pos)
{
    return nullptr;
}

void DoublyLinkedList::display_forward()
{
}

void DoublyLinkedList::display_backward()
{
}

int DoublyLinkedList::size()
{
    return 0;
}
