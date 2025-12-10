# Software Architecture

The project is built upon a **Client-Server** architecture using a custom **Entity-Component-System (ECS)** to manage game logic.

## 1. Global Architecture Layer View

The following diagram illustrates the separation of concerns between the Network layer, the Game Engine, and the resource management.

## 2. The Core: ECS (Entity Component System)

We moved away from traditional Object-Oriented inheritance for game entities to favour composition and data locality.

### Architecture Breakdown

- **Registry (The Coordinator)**: The brain of the ECS. It maps Entities to Components and manages Systems.
- **Entities**: Simple unique IDs (integers). They hold no data themselves.
- **Components**: Pure data structures (structs). Example: Position, Velocity, Sprite, Health.
- **Systems**: Logic containers. They iterate over entities possessing a specific signature of components.

### System Flow Example


## 3. Network Architecture
