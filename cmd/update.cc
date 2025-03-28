#include "../internal/task/task.h"

void runUpdateTaskCmd(const std::vector<std::string> &args) {
  if (args.size() != 2) {
    std::cout << "pls provide a task id adn the new description" << '\n';
    return;
  }
  try {
    int64_t taskId = std::stoll(args[0]);
    updateTaskDescription(taskId, args[1]);
  } catch (const std::invalid_argument &e) {
    std::cout << "Invalid task ID" << '\n';
  }
}

void runUpdateStatusCmd(const std::vector<std::string> &args,
                        TaskStatus status) {
  if (args.empty()) {
    std::cout << "Task ID is required" << std::endl;
    return;
  }
  try {
    int64_t taskId = std::stoll(args[0]);
    updateTaskStatus(taskId, status);
  } catch (const std::invalid_argument &e) {
    std::cout << "invalid task ID" << std::endl;
  }
}
