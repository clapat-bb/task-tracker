#include "../internal/task/task.h"
#include <iostream>

void runAddTaskCmd(const std::vector<std::string> &args) {
  if (args.empty()) {
    std::cout << "task description is required" << '\n';
    return;
  }
  addTask(args[0]);
}
