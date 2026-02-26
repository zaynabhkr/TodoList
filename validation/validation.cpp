#include "validation.hpp"
#include <algorithm>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <iostream>

/**
 * @brief Convert string to lowercase (ASCII-safe).
 * @note Uses std::tolower on unsigned char to avoid UB for negative char values.
 */

inline std::string to_lower_case(std::string str){
    std::string cum_str = "";
    for (auto& c:  str){
        char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        cum_str += lower_c;
    }
    return cum_str;

}

/**
 * @brief Trim leading and trailing whitespace.
 * @return A substring view copied into a new std::string.
 */

inline std::string CleanString(std::string str){
    auto is_not_white_space = [](unsigned char ch) {
            return !std::isspace(ch);
        };

        auto first = std::find_if(str.begin(), str.end(), is_not_white_space);
        auto last = std::find_if(str.rbegin(), str.rend(), is_not_white_space).base();

        return std::string(first, last);
}

/**
 * @brief Validate the completion token ("yes"/"no").
 * @return std::optional<bool> true for "yes", false for "no", nullopt on invalid input.
 */

std::optional<bool> Validation::ValidateCompletion(const std::string completed){
    std::string completed_lower = to_lower_case(completed);
    if (completed_lower == "yes") return true;
    if (completed_lower == "no") return false;
    std::cerr << "\nERROR : Invalid complete string, please write yes/no instead\n\n";
    return std::nullopt;
}

/**
 * @brief Validate priority with inclusive bounds.
 * @param priority  token to parse (expected integer).
 * @param minPriority inclusive minimum.
 * @param maxPriority inclusive maximum.
 * @return parsed integer, or nullopt with an error message.
 */
std::optional<int> Validation::ValidatePriority(const std::string priority, int minPriority, int maxPriority){
    try {
        int priority_int = std::stoi(priority);                 //
        if (priority_int < minPriority || priority_int > maxPriority){
            std::cerr << "\nERROR: priority must be between " + std::to_string(minPriority) + " and "+ std::to_string(maxPriority) + " (got "+ priority+").\n\n";
            return std::nullopt;
        }
        else{
            return priority_int;
        }
    }
    catch(std::invalid_argument&){
        std::cerr <<"\nERROR : Invalid priority type: should be an unsigned integer\n\n";
        return std::nullopt;
    }

}

/**
 * @brief Validate the task text (non-empty).
 */
std::optional<std::string> Validation::ValidateTask(const std::string line){
    if (line.empty()){
        std::cerr << "\nERROR : Invalid task type: should be a non-empty string.\n\n";
        return std::nullopt;
    }
    else{
        return line;
    }
}

/**
 * @brief Parse and validate a full input line: "task, completed(yes/no), priority(1-5)".
 * @return TaskLine on success; std::nullopt on any validation failure (non-terminating).
 */
std::optional<TaskLine> Validation::splitStringValidation(std::string line) {
    std::vector<std::string> vec;
    std::stringstream ss(line);
    std::string cumulative_str;
    // Check user provided us with three tasks
    int count_commas= std::count(line.begin(), line.end(), ',');
    if (count_commas != 2){
        std::cerr << "\nERROR: Invalid task line. It should have three components: task, completion, priority separated by commas.\n\n";
        return std::nullopt;
    }
    else{
        //Split by comma and trim each token.
        while(std::getline(ss,cumulative_str,',')){
            vec.push_back(CleanString(cumulative_str));
        }
        if (vec.size() != 3) {
                std::cerr << "\nERROR: Could not parse 3 fields.\n\n";
                return std::nullopt;
        }
        //Validate each component with detailed error messages
        auto task = ValidateTask(vec[0]);
        auto comp = ValidateCompletion(vec[1]);
        auto prio = ValidatePriority(vec[2], 1, 5);
        if (!task || !comp || !prio)
            return std::nullopt;
        return TaskLine{ *task, *comp, *prio};

    }
}

/**
 * @brief Check if a task with the same name already exists and interactively
 *        choose whether to replace it.
 *
 * Behavior:
 *  - If a duplicate by task text exists, prompt the user to (yes) replace the existing
 *    triplet or (no) skip insertion.
 *  - On "yes", deletes the old triplet and returns the new line to insert.
 *  - On "no", returns nullopt (caller skips insert).
 *  - On invalid response, re-prompts.
 *
 * @return TaskLine to insert or std::nullopt to skip.
 */
std::optional<TaskLine> Validation::CheckingDuplicates(TaskLine line, ordered_linkedlist& list){
    foundItem it = list.search_item(line);
    std::string response;
    if(it.found){
        while(response != "yes" || response !="no"){
            std::string msg =
            "\nINFO: There is a duplicate item in the TODO list. Do you want to replace \"" + it.items.task +
            "\" of priority \"" + std::to_string(it.items.priority)  +
            "\" and " + (it.items.completed ? "\"completed\"" : "\"not completed\"") + " with \""
            + line.task + "\" of priority : \"" + std::to_string(line.priority)+ "\" and " + (line.completed ? "\"completed\"" : "\"not completed\"") + "? (yes/no)\n \n ";
            std::cout << msg;
            if (!std::getline(std::cin, response)) {
                std::cerr << "Input error. Skipping insert." << std::endl;
                return std::nullopt;
            }
            if (response == "yes"){
                //Remove old occurence from the linked list.
                list.deleting_item(it.items);
                std::cout<<"\nItem changed, please continue typing your tasks, else type exit.\n\n";
                return line;
            }
            else if (response == "no"){
                std::cout<<"\nItem not changed, please continue typing your tasks, else type exit.\n\n"<<std::endl;
                return std::nullopt;
            }
            else {
                std::cerr<<std::endl<<"Please write yes/no"<<std::endl;
                continue;
            }
        }
    }
    return line;
}
