# ECS Tutorial (Draft)

This document provides a quick introduction to using our **Entity Component System (ECS)**.
It is intended as a practical guide to understand how to create entities, attach components,
and run systems inside the engine.

For an in-depth explanation of how the ECS is designed internally, please refer to
`technical_choices.md`.

---

## Overview

Our ECS is based on three core concepts:

- **Entities**: identifiers representing game objects
- **Components**: plain data structures attached to entities
- **Systems**: logic applied to entities based on their components

The goal is to keep data and behavior separate, making the engine flexible and easy to extend.

---

## Creating an Entity

Entities are lightweight objects that act as containers for components.

```cpp
Entity player;
player.addComponent<HP>(100);
player.addComponent<Position>(0.0f, 0.0f);
player.addComponent<Sprite>("../sprite/YaeMiko.jpg");
player.addComponent<Scale>(1.0f);
player.addComponent<Rotation>(0.0f);
```
 ### Each component has a single responsibility:

HP: health points

**Position**: world coordinates

**Sprite**: visual representation

**Scale**: sprite scaling factor

**Rotation**: sprite rotation angle

## Accessing Components

Components can be retrieved safely using **getComponent<T>()**.

```cpp
auto pos = player.getComponent<Position>();
if (pos) {
    std::cout << pos->getX() << ", " << pos->getY() << std::endl;
}
```
If the entity does not own the requested component, **nullptr** is returned.


## Modifying Components

Components can be modified directly by gameplay or input logic.

```cpp
auto pos = player.getComponent<Position>();
if (pos) {
    pos->setX(pos->getX() + 10.0f);
}
```

Systems will automatically reflect these changes.

## Creating the World

The **World** owns and manages all entities.

```cpp
World world;
```

Systems query the world to retrieve entities based on their components.

## Systems Overview

Systems implement all behavior.
They iterate over entities that match specific component requirements.

Our engine currently includes:

- Updater
- Draw

## Updater System

The **Updater** system synchronizes graphical data with entity components.

Responsibilities:

- Iterate over entities with a ```Sprite```

- Read ```Position```, ```Scale```, and ```Rotation```

- Apply them to the ```sf::Sprite```

```cpp
updater.update(dt, world);
```

This system does **not** handle rendering.

## Draw System

The ```Draw``` system handles rendering only.

```cpp
draw.update(dt, world);
```

It:

Iterates over entities with a ```Sprite```

Draws sprites to the render window

Never modifies component data

## Handling Input

Input logic should directly update components.

``` cpp
if (key == Up) {
    auto pos = player.getComponent<Position>();
    if (pos)
        pos->setY(pos->getY() - 10.0f);
}
```

The visual update is handled automatically by the systems.

## Example Game Structure

The ECS is designed to work inside a classic game loop.

``` cpp
World world;
Entity player;

player.addComponent<Position>(0.0f, 0.0f);
player.addComponent<Sprite>("../sprite/YaeMiko.jpg");
player.addComponent<Scale>(1.0f);
player.addComponent<Rotation>(0.0f);

Updater updater;
Draw draw(window);

while (window.isOpen()) {
    window.clear(sf::Color::Black);

    updater.updateSprites(dt, world);
    draw.update(dt, world);

    window.display();
}
```

## ECS Execution Flow

``` mathematica
Entity
 ├── Components (Position, Sprite, Scale, Rotation)
 |
World
 |
Updater  --> updates sprite transforms
Draw     --> renders sprites
```

## Adding New Behavior

To extend the engine:

**1.** Create a new Component for data

**2.** Create a new System for logic

**3.** Query the required components in the system

No existing code needs to be modified.

## Conclusion

This ECS design provides:

* Strong separation of concerns

* Clean and maintainable code

* High flexibility

* Easy scalability

This document is a draft and will evolve as the engine grows.