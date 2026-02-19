#include "node.hpp"

Node::Node(const std::string& dataValue, int priorityValue, Node* next)
    : Data(dataValue), Priority(priorityValue), Next(next) {}

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
void Node::addNode(Node* nextnode){

    //Add a new node

    Next = nextnode;
}
