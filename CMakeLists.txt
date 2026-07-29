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

add_executable(Albly_CLI main.cpp "src/ui/MainMenu.h" "src/ui/MainMenu.cpp" "src/app/App.h" "src/app/App.cpp" "src/ui/SearchScreen.h" "src/ui/SearchScreen.cpp")

target_link_libraries(
        Albly_CLI
        PRIVATE
        ftxui::ftxui
)
