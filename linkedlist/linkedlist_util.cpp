#include "linkedlist_util.hpp"
#include <cstddef>
#include <iostream>
#include <fstream>

ordered_linkedlist::ordered_linkedlist(){
        //constructor
        this->head = nullptr;
        this->size = 0;
    }
inline bool comesBefore(bool newCompleted,int newPriority, const Node* node){
    if (newCompleted != node->isCompleted()){
        // different completion status
        // if new is incomplete and node is complete -> new comes before current node
        // if new is complete and node is incomplete -> new does not come before current node
        return !newCompleted && node-> isCompleted();
    }
    return newPriority < node->GetNodePriority();
}

void ordered_linkedlist::insert(std::string newvalue, int newPriority, bool newCompleted){
        //////////////////////////////////////////////////////////////
        /*      Method to insert a node in an ordered manner        */
        //////////////////////////////////////////////////////////////
        Node* newNode = new Node(newvalue, newPriority, newCompleted, nullptr);

        //what if there is no head initalized

        if (!head){
            head =  newNode;
            size++;
            return;
        }


        if (!head || comesBefore(newCompleted, newPriority, head)) {
            newNode->addNode(head);
            head = newNode;
            ++size;
            return;
        }

        // Walk to the insertion spot
        Node* current = head;
        while (current->getNext() && !comesBefore(newCompleted, newPriority, current->getNext())) {
                current = current->getNext();
            }
        // Insert after `current`
        newNode->addNode(current->getNext());
        current->addNode(newNode);
        ++size;

    }

foundItem ordered_linkedlist::search_item(TaskLine line){
    ///////////////////////////////////////////////////////////////////////////////
    /*   Method to search if there is already a duplicate item in linkedlist     */
    ///////////////////////////////////////////////////////////////////////////////
    Node* current = head;
    while (current){
        if (current->GetNodeData() == line.task){
            return foundItem{true,current->GetNodeData()};
        }
        current = current->getNext();
    }
    return {false, line};
}

void ordered_linkedlist::deleting_item(TaskLine line){
    ///////////////////////////////////////////////////////////////////////////////
    /*                 Method to delete an item in a linked list                 */
    ///////////////////////////////////////////////////////////////////////////////
    Node* current = head;
    Node* previous = nullptr;
    while (current){
        if (current->GetNodeData() == line.task && current->GetNodePriority() == line.priority && current->isCompleted() == line.completed){
            if (current == head) {
                    head = current->getNext();
            }
            else{
            previous->addNode(current->getNext());
            }
            size--;
            return;
        }
        previous = current;
        current = current->getNext();
    }
}


void ordered_linkedlist::print_linkedlist(std::ofstream& fileoutput){
    ///////////////////////////////////////////////////////////////////////////////
    /*   Method to print a linkedlist with incomplete items into an output file   */
    ///////////////////////////////////////////////////////////////////////////////
    Node* current = head;
    while(current != nullptr) {
        if(current->isCompleted())
            fileoutput << "- [X]" << current->GetNodeData() << ", Priority: " << current->GetNodePriority() << std::endl;
        else
            fileoutput << "- []" << current->GetNodeData() << ", Priority: " << current->GetNodePriority() << std::endl;
         current = current->getNext();
    }
}

