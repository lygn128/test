cmake_minimum_required(VERSION 3.4)
set (CMAKE_CXX_STANDARD 14)
project (local)
add_executable(${PROJECT_NAME} thread_local.cc)
target_link_libraries(${PROJECT_NAME} pthread)
add_executable(cast cast.cc)
add_executable(ptr ptr.cc)

