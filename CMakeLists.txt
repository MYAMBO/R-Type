cmake_minimum_required(VERSION 3.19)

project(R-Type)

include_directories(.)

add_executable(r-type_server
        Server/main.cpp
        packet/packet.cpp
        packet/packet.hpp)

add_executable(r-type_client
        Client/main.cpp
        packet/packet.cpp
        packet/packet.hpp)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system)

