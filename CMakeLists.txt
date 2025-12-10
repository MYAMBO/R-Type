cmake_minimum_required(VERSION 3.19)

project(R-Type)

if (WIN32)
    message(STATUS "Configuring for Windows...")
elseif(UNIX)
    message(STATUS "Configuring for Linux...")
endif()

option(DEV_COMPILE "Enable strict compile warnings" OFF)

if (DEV_COMPILE)
    add_compile_options(-Werror)
endif ()

add_compile_options(-Wall -Wextra)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.x
)

FetchContent_MakeAvailable(SFML)

include_directories(.)
include_directories(./Server)

add_executable(r-type_server
        Server/main.cpp
        Server/Server.cpp
        Server/User.cpp)
        Packet/Packet.cpp
        Packet/Packet.hpp
        Packet/CustomError.hpp
        Packet/Packetreader.cpp
        Packet/Packetreader.hpp
        Packet/MyString.cpp
        Packet/MyString.hpp)

add_executable(r-type_client
        Client/main.cpp
        Packet/Packet.cpp
        Packet/Packet.hpp
        Packet/CustomError.hpp
        Packet/Packetreader.cpp
        Packet/Packetreader.hpp
        Packet/MyString.cpp
        Packet/MyString.hpp)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system)

target_link_libraries(r-type_server sfml-network)

