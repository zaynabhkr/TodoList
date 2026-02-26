#include "linkedlist_util.hpp"


ordered_linkedlist::ordered_linkedlist(){
    //constructor initializing an empty linkedlist
    this->head = nullptr;
    this->size = 0;
}

/**
 * @brief Decide whether a new item should be placed before an existing node.
 *
 * Ordering rules:
 *   - Primary key: completion status (incomplete before completed).
 *   - Secondary key: priority value (lower integer first).
 *
 * @param newCompleted  Completion of the new item (false = incomplete, true = completed).
 * @param newPriority   Priority of the new item (expected range 1..5).
 * @param node          Existing node in the list to compare against (non-null).
 * @return true  if the new item should come before @p node;
 * @return false otherwise.
 */

inline bool comesBefore(bool newCompleted,int newPriority, const Node* node){
    if (newCompleted != node->isCompleted()){
        return !newCompleted && node-> isCompleted();
        //returns true only when the new task is incomplete AND the existing node is complete
    }
    return newPriority < node->GetNodePriority();
}

/**
 * @brief Insert a new node while preserving the list's ordering invariant.
 *
 * Behavior:
 *   - Inserts at head if the list is empty or if the new item should precede the current head.
 *   - Otherwise, traverses to the first position where the new item should come
 *     before the next node, and inserts there.
 *
 * Complexity: O(n) due to linear traversal to find the insertion spot.
 *
 * @param newvalue     Task text of the new item.
 * @param newPriority  Priority (1..5); smaller means higher priority.
 * @param newCompleted Completion flag (false=incomplete, true=completed).
 */
void ordered_linkedlist::insert(std::string newvalue, int newPriority, bool newCompleted){

        Node* newNode = new Node(newvalue, newPriority, newCompleted, nullptr);

        // Case 1: Empty list → new node becomes head.
        if (!head){
            head =  newNode;
            size++;
            return;
        }

        // Case 2: Should the new node be placed before the current head?
        if (!head || comesBefore(newCompleted, newPriority, head)) {
            newNode->addNode(head);
            head = newNode;
            ++size;
            return;
        }

        // Case 3: Middle/tail insertion.
        // Traverse until the first place where the new node should come before the next node; then insert the new node right there.
        Node* current = head;
        while (current->getNext() && !comesBefore(newCompleted, newPriority, current->getNext())) {
                current = current->getNext();
        }
        // Insert newNode between `current` and `current->next`.
        newNode->addNode(current->getNext());
        current->addNode(newNode);
        ++size;
}

/**
 * @brief Search for a node by task text and return its attributes if found.
 *
 * NOTE: "Duplicate" is defined by matching the task text only, not the full triplet.
 *
 * @param line Probe containing the task text to search for.
 * @return foundItem{true, TaskLine}  if a node with the same task text exists;
 * @return foundItem{false, line}     otherwise (returns the original probe).
 */
foundItem ordered_linkedlist::search_item(TaskLine line){
    Node* current = head;
    TaskLine foundLine;
    while (current){
        if (current->GetNodeData() == line.task){
            foundLine.task = current->GetNodeData();
            foundLine.completed = current->isCompleted();
            foundLine.priority = current->GetNodePriority();
            return foundItem{true,foundLine};
        }
        current = current->getNext();
    }
    return {false, line};
}

/**
 * @brief Delete the first node that exactly matches (task, priority, completed).
 *
 * If multiple nodes have identical triplets, only the first match is removed.
 * If none match, the list is unchanged.
 *
 * @param line The (task, priority, completed) triplet to delete.
 *
 * @note Memory management: consider deleting the removed node to avoid leaks,
 *       or refactor Node ownership to smart pointers.
 */

void ordered_linkedlist::deleting_item(TaskLine line){
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

/**
 * @brief Write the entire list to a stream in Markdown-like checklist format.
 *
 * Format per line:
 *   - Completed: "- [X] Task, Priority: N"
 *   - Incomplete: "- [ ] Task, Priority: N"
 *
 * @param fileoutput Open std::ofstream to receive the formatted list.
 */

void ordered_linkedlist::print_linkedlist(std::ofstream& fileoutput){
    Node* current = head;
    while(current != nullptr) {
        if(current->isCompleted())
            fileoutput << "- [X] " << current->GetNodeData() << ", Priority: " << current->GetNodePriority() << std::endl;
        else
            fileoutput << "- [] " << current->GetNodeData() << ", Priority: " << current->GetNodePriority() << std::endl;
         current = current->getNext();
    }
}