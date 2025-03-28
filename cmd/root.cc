#include "../internal/task/task.h"
#include "add.cc"
#include "delete.cc"
#include "list.cc"
#include "update.cc"

void showHelp() {
  std::cout << "Tash Tracker is CLI tool for managing task." << std::endl;
  std::cout << "Usage:\n";
  std::cout
      << " task-tracker add <description> - Add a task to the task list\n";
  std::cout << " task-tracker list [status] - List all tasks, optionally "
               "filtered by status\n";
  std::cout << " task-tracker delete <id> - Delete a task by ID\n";
  std::cout << " task-tracker update <id> <description> - update a task's "
               "description\n";
  std::cout
      << " task-tracker mark-in-progress <id> - Mard task as in-progress\n";
  std::cout << " task-tracker mark-done <id> - Mark a task as done\n";
  std::cout << " task-tracker mark-todo <id> - Mark a task as todo\n";
}

void handleCommand(const std::vector<std::string> &args) {
  if (args.empty()) {
    showHelp();
    return;
  }
  std::string command = args[0];
  std::vector<std::string> subArgs(args.begin() + 1, args.end());

  if (command == "add") {
    runAddTaskCmd(subArgs);
  } else if (command == "list") {
    runListTaskCmd(subArgs);
  } else if (command == "delete") {
    runDeleteTaskCmd(subArgs);
  } else if (command == "update") {
    runUpdateTaskCmd(subArgs);
  } else if (command == "mark-in-progress") {
    runUpdateStatusCmd(subArgs, TaskStatus::IN_PROGRESS);
  } else if (command == "mark-todo") {
    runUpdateStatusCmd(subArgs, TaskStatus::TODO);
  } else if (command == "mark-done") {
    runUpdateStatusCmd(subArgs, TaskStatus::DONE);
  }
}
