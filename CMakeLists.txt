cmake_minimum_required(VERSION 3.10)
project(otherVersion)

set(CMAKE_CXX_STANDARD_REQUIRED 11)

include_directories(/usr/include)

add_executable(task_tracker main.cc ./internal/task/task.cc)
