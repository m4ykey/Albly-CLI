cmake_minimum_required(VERSION 4.3)

project(Albly_CLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v7.0.1
)

FetchContent_MakeAvailable(ftxui)

add_executable(Albly_CLI main.cpp)

target_link_libraries(
        Albly_CLI
        PRIVATE
        ftxui::ftxui
)
