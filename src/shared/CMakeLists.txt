cmake_minimum_required(VERSION 3.25)

project(shared)

add_library(${PROJECT_NAME} image_manipulation/change_format.cpp image_manipulation/change_resolution.cpp image_manipulation/crop.cpp)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})