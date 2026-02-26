#pragma once
#include "node.cpp"
#include <fstream>


struct TaskLine {
    std::string task;
    bool completed;
    int priority;
};

struct foundItem {
    bool found;
    TaskLine items;
};

class ordered_linkedlist{
    private:
        Node* head;
        int size;
    public:
        ordered_linkedlist();
        void insert(std::string newvalue, int newPriority, bool newCompleted);
        void print_linkedlist(std::ofstream& fileoutput);
        void deleting_item(TaskLine line);
        foundItem search_item(TaskLine line);

};