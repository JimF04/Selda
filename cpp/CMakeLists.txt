cmake_minimum_required(VERSION 3.27)
project(cpp)

find_package(jsoncpp CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp main.cpp)

target_link_libraries(cpp PRIVATE ws2_32 JsonCpp::JsonCpp)