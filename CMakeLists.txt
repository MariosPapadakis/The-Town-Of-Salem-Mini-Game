cmake_minimum_required(VERSION 3.1.4)

project(my-project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(player)

add_executable(${PROJECT_NAME}.exe assignment2.cpp)

target_include_directories(${PROJECT_NAME}.exe PUBLIC player)

target_link_directories(${PROJECT_NAME}.exe PUBLIC player)

target_link_libraries(${PROJECT_NAME}.exe PlayerLib)

target_link_libraries(${PROJECT_NAME}.exe RoundLib)
