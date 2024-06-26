cmake_minimum_required(VERSION 3.25)

project(resolution-worker)
add_executable(${PROJECT_NAME} src/main.cpp
        src/protocol/protocol.cpp
        src/protocol/protocol.h
        src/config_reader/config_reader.cpp
        src/config_reader/config_reader.h)

cmake_policy(SET CMP0135 NEW)
set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(libzmq URL https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz)
FetchContent_Declare(cppzmq URL https://github.com/zeromq/cppzmq/archive/refs/tags/v4.10.0.tar.gz)
FetchContent_Declare(Statsd URL https://github.com/vthiery/cpp-statsd-client/archive/refs/tags/v2.0.1.tar.gz)

set(ZMQ_BUILD_TESTS OFF)
set(CPPZMQ_BUILD_TESTS OFF)
set(ENABLE_TESTS OFF)

FetchContent_MakeAvailable(libzmq)
FetchContent_MakeAvailable(cppzmq)
FetchContent_MakeAvailable(Statsd)

add_subdirectory(../shared shared)

target_link_libraries(${PROJECT_NAME} PRIVATE cppzmq)
target_link_libraries(${PROJECT_NAME} PUBLIC shared)
target_link_libraries(${PROJECT_NAME} PRIVATE cpp-statsd-client)
