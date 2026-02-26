#include <string>
#include <optional>
#include "../linkedlist/linkedlist_util.cpp"


class Validation {
    public:
        std::optional<bool> ValidateCompletion(const std::string completed);
        std::optional<int> ValidatePriority(const std::string priority, int minPriority, int maxPriority);
        std::optional<std::string> ValidateTask(const std::string task);
        std::optional<TaskLine>  splitStringValidation (std::string line);
        std::optional<TaskLine> CheckingDuplicates(TaskLine line, ordered_linkedlist list);
};