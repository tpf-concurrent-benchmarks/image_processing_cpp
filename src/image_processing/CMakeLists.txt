cmake_minimum_required(VERSION 3.25)

project(image-processing)
add_executable(${PROJECT_NAME} src/main.cpp)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(libzmq URL https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz)
FetchContent_Declare(cppzmq URL https://github.com/zeromq/cppzmq/archive/refs/tags/v4.10.0.tar.gz)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_Declare(Statsd URL https://github.com/vthiery/cpp-statsd-client/archive/refs/tags/v2.0.1.tar.gz)

FetchContent_MakeAvailable(libzmq)
FetchContent_MakeAvailable(cppzmq)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(Statsd)

# add_subdirectory(../shared shared)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE cppzmq)
# target_link_libraries(image-processing-gs  PUBLIC shared)
target_link_libraries(${PROJECT_NAME} PRIVATE cpp-statsd-client)

set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

