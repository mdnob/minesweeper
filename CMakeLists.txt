cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(minesweeper src/main.cpp)
target_compile_features(minesweeper PRIVATE cxx_std_17)

target_link_libraries(minesweeper PRIVATE sfml-graphics sfml-window sfml-system)
target_include_directories(minesweeper PRIVATE ${SFML_INCLUDE_DIR})