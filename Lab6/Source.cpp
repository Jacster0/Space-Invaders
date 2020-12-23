#include "DoublyLinkedList.h"
#include <iostream>
#include <vector>

enum class Direction {Forward, Backward};

void CreateNodeArray(std::vector<Node*>& vec, int numberOfNodes);
void PrintList(const DoublyLinkedList& dll, Direction direction);

int main() {
    std::vector<Node*> nodeVector;
    Node* node1 = new(std::nothrow) Node;
    Node* node2 = new (std::nothrow)Node;

    if(node1)
        node1->setData(1024);
    if(node2)
        node2->setData(2048);
    try 
    {
        {
            DoublyLinkedList dll;
            //create some nodes and add it to the list
            CreateNodeArray(nodeVector, 4);
            for (int i = 0; i < nodeVector.size(); i++) {
                if (!dll.add(nodeVector[i], 0)) {
                    std::cout << "Error: could not add node to list" << std::endl;
                }
            }

            //print the list
            PrintList(dll, Direction::Forward);
            PrintList(dll, Direction::Backward);

            //try to remove an item out of bounds
            if (!dll.remove(24)) {
                std::cout << "Error: could not remove node from list" << std::endl;
            }
            else {
                std::cout << "node removed from list" << std::endl;
            }

            //try to remove an item in bounds
            if (!dll.remove(2)) {
                std::cout << "Error: could not remove node from list" << std::endl;
            }
            else {
                std::cout << "node removed from list" << std::endl;
            }

            //print the list
            PrintList(dll, Direction::Forward);

            //try to add node1 to an index out of bounds
            if (!dll.add(node1, 7)) {
                std::cout << "Error: could not add node to list" << std::endl;
            }
            else {
                std::cout << "Added node to list" << std::endl;
            }
            //acutally add node1 to the list
            if (!dll.add(node1, 1)) {
                std::cout << "Error: could not add node to list" << std::endl;
            }
            else {
                std::cout << "Added node to list" << std::endl;
            }

            //print the list
            PrintList(dll, Direction::Forward);

            //replace node1 with node2
            if (!dll.replace(node1, node2)) {
                std::cout << "Error: could not replace nodes" << std::endl;
            }
            else {
                std::cout << "Replaced nodes" << std::endl;
            }

            //print the list
            PrintList(dll, Direction::Forward);

            //try to replace a node that does not exist in the list
            if (!dll.replace(node1, node2)) {
                std::cout << "Error: could not replace nodes" << std::endl;
            }
            else {
                std::cout << "Replaced nodes" << std::endl;
            }

            //replace the last node with node2
            if (auto node = dll.nodeAt(dll.size() - 1)) {
                if (!dll.replace(node, node2)) {
                    std::cout << "Error: could not replace nodes" << std::endl;
                }
                else {
                    std::cout << "Replaced nodes" << std::endl;
                }
                //print the list
                PrintList(dll, Direction::Forward);
            }
            else {
                std::cout << "Error: could not find node" << std::endl;
            }

            //print the data of the first node
            if (auto node = dll.nodeAt(0)) {
                std::cout << node->getData() << std::endl;
            }
            else {
                std::cout << "Could not find node" << std::endl;
            }

            auto index = dll.search(nodeVector[0]);
            //print the index of some node if it exists
            if (index != -1) {
                std::cout << index << std::endl;
            }
            else {
                std::cout << "Could not find node" << std::endl;
            }

            //print the size of the list
            std::cout << dll.size() << std::endl;
        }
    }

    catch (...) {
        for (auto node : nodeVector) {
            delete node;
        }
        delete node1;
        delete node2;
    }

    std::cin.get();
    return 0;
}

void CreateNodeArray(std::vector<Node*>& vec, int numberOfNodes) {
    for (int i = 0; i < numberOfNodes; i++) {
        Node* node = new(std::nothrow) Node;

        if(node)
            node->setData(i + 1 << 2);

        vec.push_back(node);
    }
}

void PrintList(const DoublyLinkedList& dll, Direction direction) {
    if (direction == Direction::Forward) {
        std::cout << "Printing list forward: ";
        dll.display_forward();
    }
    else if (direction == Direction::Backward) {
        std::cout << "Printing list backward: ";
        dll.display_backward();
    }
}
