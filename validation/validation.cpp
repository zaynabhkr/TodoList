#include "validation.hpp"
#include <algorithm>
#include <cstddef>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>

inline std::string to_lower_case(std::string str){
    //////////////////////////////////////////////////////////////////////////////////////
    /*                 Function to turn a string into all lower case                    */
    //////////////////////////////////////////////////////////////////////////////////////
    std::string cum_str = "";
    for (auto& c:  str){
        char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        cum_str += lower_c;
    }
    return cum_str;

}

inline std::string CleanString(std::string str){
    //////////////////////////////////////////////////////////////////////////////////////
    /*              Function to get rid of trailing and leading whitespaces             */
    //////////////////////////////////////////////////////////////////////////////////////
    auto is_not_white_space = [](unsigned char ch) {
            return !std::isspace(ch);
        };

        auto first = std::find_if(str.begin(), str.end(), is_not_white_space);
        auto last = std::find_if(str.rbegin(), str.rend(), is_not_white_space).base();

        return std::string(first, last);
}


std::optional<bool> Validation::ValidateCompletion(const std::string completed){
    //////////////////////////////////////////////////////////////////////////////////////
    /*                Function to validate Completion portion of task line              */
    //////////////////////////////////////////////////////////////////////////////////////
    std::string completed_lower = to_lower_case(completed);
    if (completed_lower == "yes") return true;
    if (completed_lower == "no") return false;
    std::cerr << std::endl;
    std::cerr <<"ERROR : Invalid complete string, please write yes/no instead\n";
    std::cerr << std::endl;
    return std::nullopt;
}

std::optional<int> Validation::ValidatePriority(const std::string priority, int minPriority, int maxPriority){
    //////////////////////////////////////////////////////////////////////////////////////
    /*                Function to validate Priority portion of task line              */
    //////////////////////////////////////////////////////////////////////////////////////
    try {
        int priority_int = std::stoi(priority);
        if (priority_int < minPriority || priority_int > maxPriority){
            std::cerr << std::endl;
            std::cerr << "ERROR: priority must be between " + std::to_string(minPriority) + " and "+ std::to_string(maxPriority) + " (got "+ priority+").\n";
            std::cerr << std::endl;
            return std::nullopt;
        }
        else{
            return priority_int;
        }
    }
    catch(std::invalid_argument&){
        std::cerr << std::endl;
        std::cerr <<"ERROR : Invalid priority type: should be an unsigned integer\n";
        std::cerr << std::endl;
        return std::nullopt;
    }

}

std::optional<std::string> Validation::ValidateTask(const std::string line){
    //////////////////////////////////////////////////////////////////////////////////////
    /*                   Function to validate Task Portion of task line                 */
    //////////////////////////////////////////////////////////////////////////////////////
    if (line.empty()){
        std::cerr << std::endl;
        std::cerr << "ERROR : Invalid task type: should be a non-empty string.\n";
        std::cerr << std::endl;
        return std::nullopt;
    }
    else{
        return line;
    }
}

std::optional<TaskLine> Validation::splitStringValidation(std::string line) {
    //////////////////////////////////////////////////////////////////////////////////////
    /*                     Function to validate the inputted task line                  */
    /*            Returns a struct TaskLine with task, completion and priority          */
    //////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::string> vec;
    std::stringstream ss(line);
    std::string cumulative_str;
    int count_commas= std::count(line.begin(), line.end(), ',');

    if (count_commas != 2){
        std::cerr << std::endl;
        std::cerr << "ERROR: Invalid task line. It should have three components: task, completion, priority separated by commas.\n";
        std::cerr << std::endl;
        return std::nullopt;

    }
    else{
        while(std::getline(ss,cumulative_str,',')){
            vec.push_back(CleanString(cumulative_str));
        }

        if (vec.size() != 3) {
                std::cerr << std::endl;
                std::cerr << "ERROR: Could not parse 3 fields.\n";
                std::cerr << std::endl;
                return std::nullopt;
        }

        auto task = ValidateTask(vec[0]);
        auto comp = ValidateCompletion(vec[1]);
        auto prio = ValidatePriority(vec[2], 1, 5);


        if (!task || !comp || !prio)
            return std::nullopt;

        return TaskLine{ *task, *comp, *prio};

    }
}

std::optional<TaskLine> Validation::CheckingDuplicates(TaskLine line, ordered_linkedlist list){
    std::string task = line.task;
    foundItem it = list.search_item(line);
    std::string response;
    if(it.found){
        while(response != "yes" || response !="no"){
            std::string msg =
            "\nINFO: There is another item " + task +
            " in the TODO list. Do you want to replace " + line.task +
            " of priority " + std::to_string(line.priority) +
            " and " + (line.completed ? "completed" : "not completed") + " with "
            + it.items.task + "  of priority : " + std::to_string(it.items.priority) + " and " + (it.items.completed ? "completed" : "not completed") + "?(yes/no)\n \n ";

            std::cout << msg;

            std::cin>>response;

            if (response == "yes"){
                list.deleting_item(line);
                return line;
            }
            else if (response == "no"){
                return std::nullopt;
            }
            else {
                std::cerr<<std::endl;
                std::cerr<<"Please write yes/no";
                std::cerr<<std::endl;
                continue;
            }
        }
    }
    return line;


}
