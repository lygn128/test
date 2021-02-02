cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 11)
project (local)
add_executable(${PROJECT_NAME} thread_local.cc)
target_link_libraries(${PROJECT_NAME} pthread)

