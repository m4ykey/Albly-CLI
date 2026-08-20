cmake_minimum_required(VERSION 4.3)

project(Albly_CLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    ${CMAKE_SOURCE_DIR}/config.properties
    ${CMAKE_BINARY_DIR}/config.properties
    COPYONLY
)

include(FetchContent)

FetchContent_Declare(
        ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v7.0.3
)

FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
        GIT_TAG v0.53.0
)

FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.12.0
)

find_package(OpenSSL REQUIRED)

FetchContent_MakeAvailable(ftxui httplib json)

add_executable(Albly_CLI 
    main.cpp 
    "src/ui/MainMenu.cpp" 
    "src/app/App.cpp"
    "src/ui/SearchScreen.cpp"
    "src/ui/CollectionScreen.cpp" 
    "src/mapper/SearchAlbumMapper.cpp"
    "src/service/SearchAlbumService.cpp"
)

target_compile_definitions(
    Albly_CLI
    PRIVATE
    CPPHTTPLIB_OPENSSL_SUPPORT
)

target_link_libraries(
        Albly_CLI
        PRIVATE
        ftxui::ftxui
        httplib::httplib
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
        OpenSSL::Crypto
)
