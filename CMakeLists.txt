cmake_minimum_required(VERSION 3.19)

project(R-Type)

include_directories(.)

add_executable(r-type_server
        Server/main.cpp)

add_executable(r-type_client
        Client/Game/Game.cpp
        Client/main.cpp
        Client/Game/Component/HP/HP.cpp
        ECS/World.cpp
        ECS/Entity/Entity.cpp
        ECS/Component/Position/Position.cpp
        ECS/Component/Sprite/Sprite.cpp
        ECS/Component/Layer/Layer.cpp
        ECS/System/Draw/Draw.cpp
        ECS/Component/ScaleSprite/ScaleSprite.cpp
        ECS/Component/ScaleCollider/ScaleCollider.cpp
        ECS/Component/Rotation/Rotation.cpp
)

target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system)

