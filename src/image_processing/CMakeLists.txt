cmake_minimum_required(VERSION 3.25)
project(WorkerGridSearch)
add_executable(image-processing-gs src/main.cpp)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(
    CImg
    GIT_REPOSITORY https://github.com/dtschump/CImg.git
    GIT_TAG        v.2.9.5
)

FetchContent_MakeAvailable(CImg)

FetchContent_Declare(libzmq URL https://github.com/zeromq/libzmq/releases/download/v4.3.5/zeromq-4.3.5.tar.gz)
FetchContent_Declare(cppzmq URL https://github.com/zeromq/cppzmq/archive/refs/tags/v4.10.0.tar.gz)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_Declare(Statsd URL https://github.com/vthiery/cpp-statsd-client/archive/refs/tags/v2.0.1.tar.gz)

FetchContent_MakeAvailable(libzmq)
FetchContent_MakeAvailable(cppzmq)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(Statsd)
FetchContent_MakeAvailable(CImg)

# Add the CImg include directory
include_directories(${CMAKE_BINARY_DIR}/_deps/cimg-src)



target_link_libraries(image-processing-gs PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(image-processing-gs PRIVATE cppzmq)
target_link_libraries(image-processing-gs PRIVATE cpp-statsd-client)
# target_link_libraries(image-processing-gs PRIVATE CImg)
target_compile_definitions(image-processing-gs PRIVATE cimg_display=0)
