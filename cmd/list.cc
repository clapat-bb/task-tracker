#include "../internal/task/task.h"
#include <vector>

void runListTaskCmd(const std::vector<std::string> &args) {
  TaskStatus status = TaskStatus::TODO;
  if (!args.empty()) {
    status = TaskStatusFromString(args[0]);
  }
  listTasks(status);
}
