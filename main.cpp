#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include "validation/validation.cpp"
#include <string>

int main() {

    std::ofstream fileoutput;               // Output file for the final TODO list.
    ordered_linkedlist items_linkedlist;    // Maintains tasks ordered by completion and priority.
    std::string item;                       // Holds each raw/unparsed input line from the user.
    TaskLine items;                         // Parsed/validated task triplet.
    Validation v;                           // validator object since i created validation as class

    std::cout<<"LET'S CREATE YOUR TODO LIST."<<std::endl;
    fileoutput.open("output.txt");
    if(fileoutput.fail()){
        std::cout<<"failed to write file."<<std::endl;
    }
    else{
        fileoutput<<"TODO LIST"<<std::endl;
        std::cout<<"Give us the number of TODO LIST items: (type exit to finish)"<< std::endl
                <<"Give us a list of items in your checklist, whether they are completed or not (yes/no), and their priority (1-5) "<< std::endl;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*                      User can input as many tasks as they want until typing exit, hence the infinite loop.                         */
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        while(true){
            getline(std::cin,item);  // Reading a full line: "task, completed(yes/no), priority(1-5)".
            if(item == "exit"){
                break;
            }
            else if (item.empty()){
                std::cerr << std::endl<<"ERROR : Please enter a valid non-empty string with item, completion and priority."<<std::endl;
            }
            else {
            // Parse and validate the input line. Returns std::nullopt on errors (non-terminating).
            auto parsed = v.splitStringValidation(item);
                if (!parsed) {
                    // do not terminate, ask for another line.
                    continue;
                }
                items = *parsed;
                // Check for duplicates; user may choose to replace or skip.
                auto output_items = v.CheckingDuplicates(items, items_linkedlist);
                if(output_items){
                    const std::string& task = output_items->task;
                    const bool completed = output_items->completed;
                    const int priority = output_items->priority;
                    //insert in ordered position into linked list.
                    items_linkedlist.insert(task, priority,completed);
                }

            }
        }
        // Emit the final ordered list to the output file.
        items_linkedlist.print_linkedlist(fileoutput);
    }
}
