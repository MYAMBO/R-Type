cmake_minimum_required(VERSION 3.19)

project(R-Type)

include_directories(.)

add_executable(r-type_server
        Server/main.cpp
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

