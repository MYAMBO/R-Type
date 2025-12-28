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

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")
    file(DOWNLOAD
        https://raw.githubusercontent.com/cpm-cmake/CPM.cmake/master/cmake/CPM.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake"

    )
endif()
include("${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake")

CPMAddPackage(
    NAME SFML
    GITHUB_REPOSITORY SFML/SFML
    GIT_TAG 3.0.x
    EXCLUDE_FROM_ALL YES
)

include_directories(.)
include_directories(ECS)
include_directories(ECS/Component)
include_directories(ECS/Component/HP)
include_directories(ECS/Component/Tag)
include_directories(ECS/Component/Text)
include_directories(ECS/Component/Scene)
include_directories(ECS/Component/Layer)
include_directories(ECS/Component/Scale)
include_directories(ECS/Component/Button)
include_directories(ECS/Component/Group)
include_directories(ECS/Component/Camera)
include_directories(ECS/Component/Sprite)
include_directories(ECS/Component/Camera)
include_directories(ECS/Component/Script)
include_directories(ECS/Component/Damage)
include_directories(ECS/Component/Animator)
include_directories(ECS/Component/Position)
include_directories(ECS/Component/Velocity)
include_directories(ECS/Component/Rotation)
include_directories(ECS/Component/BoxCollider)
include_directories(ECS/System)
include_directories(ECS/System/Draw)
include_directories(ECS/System/Mouse)
include_directories(ECS/System/Inputs)
include_directories(ECS/System/TextSys)
include_directories(ECS/System/Movement)
include_directories(ECS/System/Animation)
include_directories(ECS/System/CameraSys)
include_directories(ECS/System/ScriptsSys)
include_directories(ECS/System/Collision)
include_directories(ECS/Entity)
include_directories(Client)
include_directories(Client/Core)
include_directories(Client/Game)
include_directories(Client/GameHelper)
include_directories(Client/ScriptsHandler)
include_directories(./Server)
include_directories(./Server/Core)
include_directories(./Packet)
include_directories(Server/Game)

add_executable(r-type_server
        Server/main.cpp
        Server/Core/Server.cpp
        Server/Core/User.cpp
        Server/Game/ServerGame.cpp
        Packet/Packet.cpp
        Packet/Packet.hpp
        Packet/CustomError.hpp
        Packet/Packetreader.cpp
        Packet/Packetreader.hpp
        Packet/MyString.cpp
        Packet/MyString.hpp
        ECS/Entity/Entity.cpp
        ECS/System/Inputs/Inputs.cpp
        ECS/System/Animation/Animation.cpp
        ECS/System/CameraSys/CameraSys.cpp
        ECS/System/Movement/Movement.cpp
        ECS/System/ScriptsSys/ScriptsSys.cpp
        ECS/World.cpp
        ECS/Component/HP/HP.cpp
        Client/GameHelper/GameHelper.cpp
        ECS/Component/Tag/Tag.cpp
        ECS/Component/Scale/Scale.cpp
        ECS/Component/Layer/Layer.cpp
        ECS/Component/Scene/Scene.cpp
        ECS/Component/Group/Group.cpp
        ECS/Component/Script/Script.cpp
        ECS/Component/Sprite/Sprite.cpp
        ECS/Component/Camera/Camera.cpp
        ECS/Component/Position/Position.cpp
        ECS/Component/Velocity/Velocity.cpp
        ECS/Component/Rotation/Rotation.cpp
        ECS/Component/Animator/Animator.cpp
        ECS/Component/BoxCollider/BoxCollider.cpp
        Server/IGameNetwork.hpp)

add_executable(r-type_client
        Client/main.cpp
        Client/Game/Game.cpp
        Client/GameHelper/GameHelper.cpp
        Client/ScriptsHandler/ScriptsHandler.cpp
        ECS/Entity/Entity.cpp
        ECS/System/Draw/Draw.cpp
        ECS/System/Mouse/Mouse.cpp
        ECS/System/Inputs/Inputs.cpp
        ECS/System/TextSys/TextSys.cpp
        ECS/System/Movement/Movement.cpp
        ECS/System/Animation/Animation.cpp
        ECS/System/CameraSys/CameraSys.cpp
        ECS/System/Collision/Collision.cpp
        ECS/System/ScriptsSys/ScriptsSys.cpp
        ECS/World.cpp
        ECS/Component/HP/HP.cpp
        ECS/Component/Tag/Tag.cpp
        ECS/Component/Text/Text.cpp
        ECS/Component/Scale/Scale.cpp
        ECS/Component/Layer/Layer.cpp
        ECS/Component/Group/Group.cpp
        ECS/Component/Scene/Scene.cpp
        ECS/Component/Button/Button.cpp
        ECS/Component/Script/Script.cpp
        ECS/Component/Sprite/Sprite.cpp
        ECS/Component/Camera/Camera.cpp
        ECS/Component/Damage/Damage.cpp
        ECS/Component/Position/Position.cpp
        ECS/Component/Velocity/Velocity.cpp
        ECS/Component/Rotation/Rotation.cpp
        ECS/Component/Animator/Animator.cpp
        ECS/Component/BoxCollider/BoxCollider.cpp
        Packet/Packet.cpp
        Packet/MyString.cpp
        Client/Core/Network.cpp
        Client/Core/ClientPacketreader.cpp)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system sfml-network)

target_link_libraries(r-type_server  sfml-graphics sfml-system sfml-network)