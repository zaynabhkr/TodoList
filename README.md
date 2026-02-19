#  HOW TO RUN CODE:

2 simple steps in terminal:
- g++ main.cpp -o main
- ./main

# PROJECT STRUCTURE:

 ├─ main.cpp\
 └─ linkedlist\
   └─ linkedlist_util.cpp   # ordered_linkedlist class\
    └─ linkedlist_util.hpp   # ordered_linkedlist helpers\
    └─ node.cpp\
    └─ node.hpp


**main.cpp** includes linkedlist/linkedlist_util.cpp and expects an ordered_linkedlist type that supports:\

insert(const std::string& task, int priority)\
print_linkedlist_incomplete(std::ofstream& out)\
print_linkedlist_complete(std::ofstream& out)


*  Implementation High Level:

1/ Asks how many checklist items you want to enter.\
2/ For each item, reads a single line formatted as task, yes|no, priority.\
3/ Validates input:
- completed must be exactly "yes" or "no" (asserted).\
- priority must be an integer in [1, 5] (asserted).
4/ Items are stores in linked list for completed and non completed items using insertion sort method in the linkedlist class.\
4/ The code writes a file back **output.txt** with the full TODO list with checked marks **[X]** if the item is completed or not checked mark **[]** if the item is not completed.

# Linkedlist class

I created a folder named **linkedlist** with two util classes:
* Node.hpp gives us the general declarations of the node element with its methods (getters and setters), most important one is adding a new Node to the *Next* one
* Node.cpp gives us the initializations of these methods and class attributes of Node.
* linkedlist.hpp calls on the reference of the object Node to create a chain of ordered Nodes thanks to its main method insert which helps insert in a ordered manner with priority level.
* linkedlist.cpp:
* **insert method**: We have to keep in mind that the method is conscient that if the new node is to be inserted before head or is the init head or is being inserted between two nodes (based on ordered priority from low int to high int)
* **print method**: method to print the linked list nodes one by one in the output file parameter.


#  Handling reading the input:

When reading the lines of input with the fstream library, I used two functions to clean and split the tasks delimited with commas:
* **CleanString:** is a function that allows me to remove the trailing and leading whitespaces in a string.
* **SplitString:** is a function that allows me to split a full line of tasks *(e.g : shower, yes, 1)* into separate **CleanString** strings in a vector *(e.g : ["shower", "yes", 1] )*

#  Handling adding tasks that are completed or not:

**linkedlist/linkedlist_util.cpp** provides an ordered singly-linked list abstraction:

- Insertion keeps order by priority (low number → higher priority → earlier in the list).
- Separate lists for completed and incomplete tasks allow writing them in two blocks.
- Printing functions format items into the output stream.

If you extend the node to store the completion flag, you could merge the lists and still print in two sections by filtering at print time, but the current design keeps the logic simple.

#  Handling writing the file:
- for items that are completed we just outsource them into the output file **output.txt** using the **print_linkedlist_complete** method in linkedlist class.
```c
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
```
- for items that are incomplete we just outsource them into the output file **output.txt** using the **print_linkedlist_incomplete** method in linkedlist class.
```c

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

```
