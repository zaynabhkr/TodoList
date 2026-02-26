#pragma once
#include <string>

class Node {
    private:
        std::string Data;
        int Priority;
        Node* Next;
        bool completed;
    public:
        Node(const std::string& dataValue, int priorityValue, bool completedValue, Node* next = nullptr);
        std::string GetNodeData()const ;
        int GetNodePriority() const ;
        Node* getNext() const ;
        bool isCompleted() const;
        void addNode(Node* nextnode);
};