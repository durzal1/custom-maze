cmake_minimum_required(VERSION 3.17)
project(custom_maze)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.cpp maze.h maze.cpp)
add_executable(custom_maze ${SOURCE_FILES})
target_link_libraries(custom_maze mingw32 SDL2main SDL2)
