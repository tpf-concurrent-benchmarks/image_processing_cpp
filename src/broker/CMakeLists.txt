cmake_minimum_required(VERSION 3.25)
project(broker)

add_executable(${PROJECT_NAME} src/main.cpp
        src/protocol/protocol.cpp
        src/protocol/protocol.h
        src/config_reader/config_reader.cpp
        src/config_reader/config_reader.h)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(libzmq URL https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz)
FetchContent_Declare(cppzmq URL https://github.com/zeromq/cppzmq/archive/refs/tags/v4.10.0.tar.gz)

set(ZMQ_BUILD_TESTS OFF)
set(CPPZMQ_BUILD_TESTS OFF)

FetchContent_MakeAvailable(libzmq)
FetchContent_MakeAvailable(cppzmq)


target_link_libraries(${PROJECT_NAME} PRIVATE cppzmq)

set(DOWNLOAD_EXTRACT_TIMESTAMP True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

