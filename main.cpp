#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "validation/validation.cpp"
#include <string>




int main() {

    std::ifstream file;
    std::ofstream fileoutput;
    ordered_linkedlist items_linkedlist;
    int priority_task;
    std::string item;
    TaskLine items;
    size_t i = 0;
    Validation v;
    std::cout<<"LET'S CREATE YOUR TODO LIST."<<std::endl;

    fileoutput.open("output.txt");
    if(fileoutput.fail()){
                std::cout<<"failed to write file."<<std::endl;
    }
    else{
        fileoutput<<"TODO LIST"<<std::endl;
        std::cout<<"Give us the number of TODO LIST items: (type exit to finish)"<<std::endl;
        std::cout<<"Give us a list of items in your checklist, whether they are completed or not (yes/no), and their priority (1-5) "<<std::endl;
        while(true){

            getline(std::cin,item);
            if(item == "exit"){
                break;
            }
            else if (item.empty()){
                std::cerr << std::endl;
                std::cerr<<"ERROR : Please enter a valid non-empty string with item, completion and priority."<<std::endl;
                std::cerr << std::endl;
            }
            else {
            auto parsed = v.splitStringValidation(item);

                if (!parsed) {
                    continue; // do not terminate; just ask for another line
                }

                // Use the validated result
                items = *parsed;
                const std::string& task = items.task;
                const bool completed = items.completed;
                const int priority = items.priority;

                items_linkedlist.insert(task, priority,completed);
                i++;
            }
        }
        items_linkedlist.print_linkedlist(fileoutput);
    }
}
