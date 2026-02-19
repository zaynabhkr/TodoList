#pragma once
#include "node.cpp"
#include <fstream>

class ordered_linkedlist{
    private:
        Node* head;
        int size;
    public:
        ordered_linkedlist();
        void insert(std::string newvalue, int newPriority);
        void print_linkedlist_complete(std::ofstream& fileoutput);
        void print_linkedlist_incomplete(std::ofstream& fileoutput);
};