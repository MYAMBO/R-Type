# R-Type Project

## Overview

R-Type is a modern reimplementation of the classic arcade shooter with a focus on:

* **Real-time multiplayer gameplay** with custom UDP/TCP networking
* **Modular game engine** powered by a custom Entity Component System (ECS)
* **Cross-platform support** (Linux, Windows)
* **Professional architecture** designed for scalability and maintainability

---

## Features

### Gameplay

* Classic R-Type shoot 'em up mechanics
* Multiplayer support (up to 4 players)
* Real-time synchronized gameplay
* Multiple enemy types and wave patterns
* Scrolling background system

---

### [Technical Choices](docs/technical_choices.md)

* **Custom ECS Architecture** - Data-oriented design for optimal performance
* **Dual Protocol Networking** - TCP for reliability, UDP for real-time updates
* **Fail-Soft Asset Loading** - Game continues even with missing assets
* **Component-Based Design** - Easy to extend and maintain
* **CMake Build System** - Modern, portable build configuration

## Quick Start

### Prerequisites

| Requirement          | Version                                   | Notes                                                     |
|:---------------------|:------------------------------------------|:----------------------------------------------------------|
| **OS**               | Linux (primary), Windows           | Cross-platform support               |
| **CMake**            | 3.20+            | Build system        |
| **SFML**                 | 3.0+         | Graphics and networking |

---

## Building the Project

``` bash
# Clone the repository
git clone https://github.com/MYAMBO/R-Type.git
cd R-Type

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the server
./r-type_server -p 4444 -u 1111

# Run the client (in another terminal)
./r-type_client -p 4444 -u localhost
```



---

 ### Core Technologies

<div align="center">

| Component       | Technology        | Purpose                                   |
|-----------------|-------------------|-------------------------------------------|
| Game Engine     | Custom ECS        | Entity management and game logic          |
| Graphics        | SFML 3.0+         | Rendering and window management           |
| Networking      | SFML Network      | TCP / UDP communication                   |
| Build System    | CMake + CPM       | Dependency management                     |

</div>

---

##  Entity Component System (ECS)

Our custom ECS provides a flexible, data-oriented architecture:

### Components

<details>
<summary><b>Transform Components</b> (click to expand)</summary>

| Component                                  | Description                          | Key Methods                                               |
|--------------------------------------------|--------------------------------------|-----------------------------------------------------------|
| [Position](docs/ECS/component/Position.md) | 2D world coordinates                 | getX(), getY(), setX(), setY()                             |
| [Rotation](docs/ECS/component/Rotation.md) | Rotation angle in degrees            | getRotation(), setRotation()                               |
| [Scale](docs/ECS/component/Scale.md)       | Uniform or non-uniform scaling       | getScale(), setScale()                                     |
| [Velocity](docs/ECS/component/Velocity.md) | Movement speed on X and Y axes       | getVelocityX(), getVelocityY(), setVelocityX(), setVelocityY() |

</details>

<details>
<summary><b>Rendering Components</b> (click to expand)</summary>

| Component                                  | Description                          | Key Methods                                               |
|--------------------------------------------|--------------------------------------|-----------------------------------------------------------|
| [Sprite](docs/ECS/component/Sprite.md)     | Visual representation (texture)      | getSprite(), setSprite()                                   |
| [Animator](docs/ECS/component/Animator.md) | Sprite sheet animation system        | getCurrentFrame(), setFrameRate(), getFrameRect()          |
| [Layer](docs/ECS/component/Layer.md)       | Rendering order and priority         | getLayerId(), setLayerId()                                 |
| [Camera](docs/ECS/component/Camera.md)     | View and viewport control            | getView(), setPosition(), setSize()                        |

</details>

<details>
<summary><b>Gameplay Components</b> (click to expand)</summary>

| Component                                        | Description                          | Key Methods                                               |
|--------------------------------------------------|--------------------------------------|-----------------------------------------------------------|
| [HP](docs/ECS/component/HP.md)                   | Health points system                 | getHP(), setHP(), getMaxHP(), isAlive()                    |
| [BoxCollider](docs/ECS/component/BoxCollider.md) | Collision detection box              | getSize(), getOffset(), isTrigger(), isVisible()           |
| [Script](docs/ECS/component/Script.md)           | Custom behavior logic                | getScript(), setScript()                                   |

</details>

<details>
<summary><b>Organization Components</b> (click to expand)</summary>

| Component                            | Description                          | Key Methods                       |
|--------------------------------------|--------------------------------------|-----------------------------------|
| [Tag](docs/ECS/component/Tag.md)     | String identifier for entities       | getTag(), setTag()                |
| [Scene](docs/ECS/component/Scene.md) | Scene membership and grouping        | getScene(), setScene()            |

</details>


----------
Made by Yanis Monté / Martin Bonte / Timoté Koenig / Pierre Ryssen / Antoine Orange