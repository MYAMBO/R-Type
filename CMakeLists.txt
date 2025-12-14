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
include_directories(ECS)
include_directories(ECS/Component)
include_directories(ECS/Component/HP)
include_directories(ECS/Component/Tag)
include_directories(ECS/Component/Scene)
include_directories(ECS/Component/Layer)
include_directories(ECS/Component/Scale)
include_directories(ECS/Component/Camera)
include_directories(ECS/Component/Sprite)
include_directories(ECS/Component/Camera)
include_directories(ECS/Component/Script)
include_directories(ECS/Component/Animator)
include_directories(ECS/Component/Position)
include_directories(ECS/Component/Velocity)
include_directories(ECS/Component/Rotation)
include_directories(ECS/Component/BoxCollider)
include_directories(ECS/System)
include_directories(ECS/System/Draw)
include_directories(ECS/System/Updater)
include_directories(ECS/System/Inputs)
include_directories(ECS/Entity)
include_directories(Client)
include_directories(Client/Game)
include_directories(Client/GameHelper)
include_directories(./Server)
include_directories(./Packet)
include_directories(Server/Game)

add_executable(r-type_server
        Server/main.cpp
        Server/Server.cpp
        Server/User.cpp
        Packet/Packet.cpp
        Packet/Packet.hpp
        Packet/CustomError.hpp
        Packet/Packetreader.cpp
        Packet/Packetreader.hpp
        Packet/MyString.cpp
        Packet/MyString.hpp)

add_executable(r-type_client
        Client/main.cpp
        Client/Game/Game.cpp
        Client/GameHelper/GameHelper.cpp
        ECS/Entity/Entity.cpp
        ECS/System/Draw/Draw.cpp
        ECS/System/Inputs/Inputs.cpp
        ECS/System/Updater/Updater.cpp
        ECS/World.cpp
        ECS/Component/HP/HP.cpp
        ECS/Component/Tag/Tag.cpp
        ECS/Component/Scale/Scale.cpp
        ECS/Component/Layer/Layer.cpp
        ECS/Component/Scene/Scene.cpp
        ECS/Component/Script/Script.cpp
        ECS/Component/Sprite/Sprite.cpp
        ECS/Component/Camera/Camera.cpp
        ECS/Component/Position/Position.cpp
        ECS/Component/Velocity/Velocity.cpp
        ECS/Component/Rotation/Rotation.cpp
        ECS/Component/Animator/Animator.cpp
        ECS/Component/BoxCollider/BoxCollider.cpp
        Packet/Packet.cpp
        Packet/Packet.hpp
        Packet/CustomError.hpp
        Packet/Packetreader.cpp
        Packet/Packetreader.hpp
        Packet/MyString.cpp
        Packet/MyString.hpp)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system sfml-network)

target_link_libraries(r-type_server sfml-network)