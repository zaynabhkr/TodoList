#include "node.hpp"

Node::Node(const std::string& dataValue, int priorityValue, bool completedValue, Node* next)
    : Data(dataValue), Priority(priorityValue), completed(completedValue), Next(next) {}

std::string Node::GetNodeData()const {

    //Get Node Data

    return Data;
};
int Node::GetNodePriority() const {

    //Get Node Priority

    return Priority;
};
Node* Node::getNext() const {

    //Get the next Node

    return Next;

}
bool Node::isCompleted() const {

    //Get the next Node

    return completed;
}

void Node::addNode(Node* nextnode){

    //Add a new node

    Next = nextnode;
}
