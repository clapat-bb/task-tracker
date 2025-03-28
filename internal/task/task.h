#ifndef TASK_H
#define TASK_H

#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

enum class TaskStatus { TODO, IN_PROGRESS, DONE };

struct Task {
  int64_t id;
  std::string description;
  TaskStatus status;
  time_t createAt;
  time_t updateAt;
};

std::string TaskStatusToString(TaskStatus status);
TaskStatus TaskStatusFromString(const std::string &status);
std::string statusColor(TaskStatus status);
std::vector<Task> readTaskFromFile();
void wirteTasksToFile(std::vector<Task> &tasks);
Task *newTask(int64_t id, const std::string &description);
void listTasks(TaskStatus status);
void addTask(const std::string &description);
void listTasks(TaskStatus status);
void deleteTask(int64_t id);
void updateTaskStatus(int64_t id, TaskStatus status);
void updateTaskDescription(int64_t id, const std::string &description);

#endif // !TASK_H
