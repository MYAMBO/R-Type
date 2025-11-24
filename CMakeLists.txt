cmake_minimum_required(VERSION 3.19)

project(R-Type)

include_directories(.)

add_executable(r-type_server
        Server/main.cpp)

add_executable(r-type_client
        Client/Game/Game.cpp
        Client/main.cpp
        ECS/World.cpp
        ECS/Entity/Entity.cpp
        ECS/Entity/Component/HP/HP.cpp
        ECS/Entity/Component/Position/Position.cpp
        ECS/Entity/Component/Sprite/Sprite.cpp
        ECS/System/Draw/Draw.cpp
)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system)

