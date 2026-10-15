cmake_minimum_required(VERSION 3.27)
project("LeaderSort")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(LeaderSort
    "main.cpp"
    "LeaderSortUI.cpp"
    "LeaderSortUI.h"
)

target_link_libraries(LeaderSort PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)