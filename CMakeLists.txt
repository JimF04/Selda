cmake_minimum_required(VERSION 3.22)
project(Selda C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp CONFIG REQUIRED)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

add_executable(${PROJECT_NAME} src/main.cpp
        src/Mapa.cpp
        src/Mapa.h
        src/Enemy/Enemy.cpp
        src/Enemy/Enemy.h
        src/ball.cpp
        src/ball.h
        src/Nivel.h
        src/Niveles/Nivel1.cpp
        src/Niveles/Nivel1.h
        src/Niveles/Nivel2.cpp
        src/Niveles/Nivel2.h
        src/Niveles/Nivel3.cpp
        src/Niveles/Nivel3.h
        src/Niveles/Nivel4.cpp
        src/Niveles/Nivel4.h
        src/Niveles/Nivel5.cpp
        src/Niveles/Nivel5.h

)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib JsonCpp::JsonCpp)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release mode
