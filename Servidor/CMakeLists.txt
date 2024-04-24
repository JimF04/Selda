cmake_minimum_required(VERSION 3.28)
project(Servidor)

find_package(Crow)
find_package(jsoncpp CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Servidor main.cpp
)


target_link_libraries(Servidor PUBLIC Crow::Crow JsonCpp::JsonCpp)