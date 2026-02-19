#pragma once
#include <string>

class Node {
    private:
        std::string Data;
        int Priority;
        Node* Next;
    public:
        Node(const std::string& dataValue, int priorityValue, Node* next = nullptr);
        std::string GetNodeData()const ;
        int GetNodePriority() const ;
        Node* getNext() const ;
        void addNode(Node* nextnode);
};