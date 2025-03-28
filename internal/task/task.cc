#include "task.h"
#include <cstdint>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <json.hpp>

namespace fs = std::filesystem;

std::string TaskStatusToString(TaskStatus status) {
  switch (status) {
  case TaskStatus::TODO:
    return "todo";
  case TaskStatus::IN_PROGRESS:
    return "in_progress";
  case TaskStatus::DONE:
    return "done";
  default:
    return "unkonw";
  }
}

TaskStatus TaskStatusFromString(const std::string &status) {
  if (status == "todo") {
    return TaskStatus::TODO;
  }
  if (status == "in_progress") {
    return TaskStatus::IN_PROGRESS;
  }
  if (status == "done") {
    return TaskStatus::DONE;
  }
  return TaskStatus::TODO;
}

std::string statusColor(TaskStatus status) {
  switch (status) {
  case TaskStatus::TODO:
    return "#3c3c3c";
  case TaskStatus::IN_PROGRESS:
    return "#202020";
  case TaskStatus::DONE:
    return "#04b575";
  default:
    return "#3c3c3c";
  }
}

std::vector<Task> readTaskFromFile() {
  std::string filePath = fs::current_path().string() + "/tasks.json";
  if (!fs::exists(filePath)) {
    std::ofstream file(filePath);
    file << "[]";
    file.close();
    return {};
  }

  std::ifstream file(filePath);
  json j;
  file >> j;

  std::vector<Task> tasks;
  for (const auto &taskJson : j) {
    Task task;
    task.id = taskJson["id"];
    task.description = taskJson["description"];

    if (taskJson["status"].is_string()) {
      task.status = TaskStatusFromString(taskJson["status"]);
    } else if (taskJson["status"].is_number()) {
      int statusInt = taskJson["status"];
      switch (statusInt) {
      case 0:
        task.status = TaskStatus::TODO;
        break;
      case 1:
        task.status = TaskStatus::IN_PROGRESS;
        break;
      case 2:
        task.status = TaskStatus::DONE;
        break;
      default:
        std::cerr << "Error: unkonw status value in task with id " << task.id
                  << '\n';
        continue;
      }
    } else {
      std::cerr << "Error: status field has an unexpected type in task with id "
                << task.id << "\n";
      continue;
    }
    task.createAt = taskJson["createAt"];
    task.updateAt = taskJson["updateAt"];
    tasks.push_back(task);
  }
  return tasks;
}

void writeTasksToFile(const std::vector<Task> &tasks) {
  std::string filePath = fs::current_path().string() + "/tasks.json";
  std::ofstream file(filePath);
  json j = json::array();
  for (const auto &task : tasks) {
    json taskJson;
    taskJson["id"] = task.id;
    taskJson["description"] = task.description;
    taskJson["status"] = task.status;
    taskJson["createAt"] = task.createAt;
    taskJson["updateAt"] = task.updateAt;
    j.push_back(taskJson);
  }
  file << std::setw(4) << j;
  file.close();
}

Task *newTask(int64_t id, const std::string &description) {
  auto task =
      new Task{id, description, TaskStatus::TODO, time(nullptr), time(nullptr)};
  return task;
}

void listTasks(TaskStatus status) {
  auto tasks = readTaskFromFile();
  if (tasks.empty()) {
    std::cout << "no tasks found" << std::endl;
    return;
  }

  std::vector<Task> filteredTasks;
  if (status == TaskStatus::TODO || status == TaskStatus::IN_PROGRESS ||
      status == TaskStatus::DONE) {
    for (const auto &task : tasks) {
      if (task.status == status) {
        filteredTasks.push_back(task);
      } else {
        filteredTasks = tasks;
      }
      std::cout << "Tasks (" << TaskStatusToString(status) << ")" << std::endl;
      for (const auto &task : filteredTasks) {
        std::cout << "ID:" << task.id << " " << TaskStatusToString(task.status)
                  << " " << task.description << " ("
                  << std::put_time(localtime(&task.updateAt),
                                   "%Y-%m-%d %H:%M:%S")
                  << ")" << '\n';
      }
    }
  }
}

void addTask(const std::string &description) {
  auto tasks = readTaskFromFile();
  int64_t newTaskID = 1;
  if (!tasks.empty()) {
    newTaskID = tasks.back().id + 1;
  }

  auto task = newTask(newTaskID, description);
  tasks.push_back(*task);
  delete task;

  std::cout << "Task added successfully: (ID: " << newTaskID << ")" << '\n';
  writeTasksToFile(tasks);
}

void deleteTask(int64_t id) {
  auto tasks = readTaskFromFile();
  std::vector<Task> updatedTask;
  bool taskFound = false;
  for (const auto &task : tasks) {
    {
      if (task.id != id) {
        updatedTask.push_back(task);

      } else {
        taskFound = true;
      }
    }
    if (!taskFound) {
      std::cout << "Task not found (ID: " << id << ")" << std::endl;
      return;
    }
    std::cout << "Task deleted successfully: （ID: " << id << ")" << std::endl;
    writeTasksToFile(updatedTask);
  }
}

void updateTaskStatus(int64_t id, TaskStatus status) {
  auto tasks = readTaskFromFile();
  bool taskFound = false;
  for (auto &task : tasks) {
    if (task.id == id) {
      task.status = status;
      task.updateAt = std::time(nullptr);
      taskFound = true;
      break;
    }
  }
  if (!taskFound) {
    std::cout << "Task not found (ID: " << id << ")" << '\n';
    return;
  }
  std::cout << "Task found successfully (ID: " << id << ")" << '\n';
  writeTasksToFile(tasks);
}

void updateTaskDescription(int64_t id, const std::string &description) {
  auto tasks = readTaskFromFile();
  bool taskFound = false;
  for (auto &task : tasks) {
    if (task.id == id) {
      task.description = description;
      task.updateAt = std::time(nullptr);
      taskFound = true;
      break;
    }
  }

  if (!taskFound) {
    std::cout << "Task not found (ID: " << id << ")" << '\n';
  }
  std::cout << "Task found successfully: (ID: " << id << ")" << '\n';
  writeTasksToFile(tasks);
}
