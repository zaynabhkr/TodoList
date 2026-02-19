#include <string>
#include <optional>
struct TaskLine {
    std::string task;
    bool completed;
    int priority;
};

class Validation {
    public:
        std::optional<bool> ValidateCompletion(const std::string completed);
        std::optional<int> ValidatePriority(const std::string priority, int minPriority, int maxPriority);
        std::optional<std::string> ValidateTask(const std::string task);
        std::optional<TaskLine>  splitStringValidation (std::string line);
};