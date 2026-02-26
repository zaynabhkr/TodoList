#pragma once
#include "node.cpp"
#include <fstream>
#include <fstream>


/// A single task with its name, completion status, and priority.
struct TaskLine {
    std::string task;
    bool completed;
    int priority;
};

/// Result of searching for a task: whether it was found and the matching item.
struct foundItem {
    bool found;
    TaskLine items;
};

class ordered_linkedlist{
    private:
        Node* head;         // First node in the list
        int size;           // Number of items
    public:
        ordered_linkedlist();
        void insert(std::string newvalue, int newPriority, bool newCompleted);
        void print_linkedlist(std::ofstream& fileoutput);
        void deleting_item(TaskLine line);
        foundItem search_item(TaskLine line);
        void print_to_console();
};