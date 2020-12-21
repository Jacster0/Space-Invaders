#include "DoublyLinkedList.h"
#include <iostream>

int main() {
    {
        DoublyLinkedList list;
        Node* node1 = new Node;
        node1->setData(52);

        Node* node2 = new Node;
        node2->setData(103);

        Node* node3 = new Node;
        node3->setData(500);

        Node* node4 = new Node;
        node4->setData(1478);

        Node* node5 = new Node;
        node5->setData(256);

        Node* node6 = new Node;
        node6->setData(512);

        list.add(node1, 0);
        list.add(node2, 1);
        list.add(node5, 1);

        std::cout << "DISPLAYING FORWARD: " << std::endl;
        list.display_forward();
        std::cout << std::endl;
        std::cout << "DISPLAYING BACKWARD: " << std::endl;
        list.display_backward();

        std::cout << "\nPRINT SIZE: " << std::endl;
        std::cout << list.size() << std::endl;
        list.remove(1);
        std::cout << "\nPRINT SIZE AFTER REMOVAL: " << std::endl;
        std::cout << list.size() << std::endl;

        std::cout << std::endl;

        std::cout << "DISPLAYING FORWARD: " << std::endl;
        list.display_forward();

        std::cout << std::endl;

        list.replace(node2, node3);
        std::cout << "DISPLAYING FORWARD AFTER REPLACE: " << std::endl;
        list.display_forward();

        std::cout << "\nPRINT INDEX OF A GIVEN NODE (IF IT EXISTS): " << std::endl;
        std::cout << list.search(node3) << std::endl;
        std::cout << list.search(node4) << std::endl;

        std::cout << std::endl;

        list.add(node4, 2);
        std::cout << "DISPLAYING FORWARD AFTER ADD: " << std::endl;
        list.display_forward();
        std::cout << std::endl;
        std::cout << "\nDISPLAYING BACKWARD AFTER ADD: " << std::endl;
        list.display_backward();

        list.add(node6, 4);
        std::cout << "\nDISPLAYING FORWARD AFTER ADD: " << std::endl;
        list.display_forward();

        list.remove(5);
        std::cout << "\nDISPLAYING FORWARD AFTER REMOVING TAIL: " << std::endl;
        list.display_forward();
    }
   
    std::cin.get();
    return 0;
}