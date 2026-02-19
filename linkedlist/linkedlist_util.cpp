#include "linkedlist_util.hpp"
#include <iostream>
#include <fstream>

ordered_linkedlist::ordered_linkedlist(){
        //constructor
        this->head = nullptr;
        this->size = 0;
    }
void ordered_linkedlist::insert(std::string newvalue, int newPriority){
        //////////////////////////////////////////////////////////////
        /*      Method to insert a node in an ordered manner        */
        //////////////////////////////////////////////////////////////
        Node* newNode = new Node(newvalue, newPriority, nullptr);
        Node* current = head;

        //what if there is no head initalized

        if (!head){
            head =  newNode;
            size++;
            return;
        }

        //what if it needs to be inserted before the head

        if (current->GetNodePriority()>=newPriority){
            newNode->addNode(head);
            head = newNode;
            size++;
            return;
        }

        //if it needs to be inserted between two nodes

        while(current->getNext() && newPriority>=current->getNext()->GetNodePriority()){
            current = current->getNext();
        }
        newNode->addNode(current->getNext());
        current->addNode(newNode);
        size++;
    }

void ordered_linkedlist::print_linkedlist_complete(std::ofstream& fileoutput){
    ///////////////////////////////////////////////////////////////////////////////
    /*   Method to print a linkedlist with completed items into an output file   */
    ///////////////////////////////////////////////////////////////////////////////
    Node* current = head;
    while(current != nullptr) {
        fileoutput << "- [X]" << current->GetNodeData() << ", Priority: " << current->GetNodePriority() << std::endl;
        current = current->getNext();
    }
}

void ordered_linkedlist::print_linkedlist_incomplete(std::ofstream& fileoutput){
    ///////////////////////////////////////////////////////////////////////////////
    /*   Method to print a linkedlist with incomplete items into an output file   */
    ///////////////////////////////////////////////////////////////////////////////
    Node* current = head;
    while(current != nullptr) {
        fileoutput << "- []" << current->GetNodeData() << ", Priority: " << current->GetNodePriority() << std::endl;
        current = current->getNext();
    }
}

