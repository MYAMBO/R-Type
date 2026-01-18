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

## ECS (Entity Component System)

You can find everything talking about the ECS [here](docs/ECS.md)

----------
Made by Yanis Monté / Martin Bonte / Timoté Koenig / Pierre Ryssen / Antoine Orange