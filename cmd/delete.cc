#include "../internal/task/task.h"
#include <cstdint>
#include <iostream>
#include <stdexcept>

void runDeleteTaskCmd(const std::vector<std::string> &args) {
  if (args.size() != 1) {
    std::cout << "please provide a task ID" << '\n';
    return;
  }
  try {
    int64_t taskID = std::stoll(args[0]);
    deleteTask(taskID);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid task ID" << '\n';
  }
}
