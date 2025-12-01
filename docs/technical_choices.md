## Entities

Entities are unique identifiers that can have multiple Components attached.  
They do not contain data or behavior themselves; they simply act as containers for Components.

| Concept | Description |
| :--- | :--- |
| **Entity** | Represents a game object. Can dynamically add/remove Components. Systems operate on entities with specific Components. |

---

## Components

Components are simple data containers. They do not contain logic. In our engine, the following Components are available:

| Component | Description                                                                                                                                                                                           |
| :--- |:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **HP** | Stores the health points of an entity.                                                                                                                                                                |
| **Position** | Stores the X and Y coordinates of an entity.                                                                                                                                                          |
| **Rotation** | Stores the rotation angle of an entity in degrees.                                                                                                                                                    |
| **Scale** | Stores scaling factors along X and Y axes.                                                                                                                                                            |
| **Sprite** | Holds the visual representation (`sf::Sprite`) of an entity.                                                                                                                                          |
| **Velocity** | Stores a single float value representing the speed of an entity. Can be retrieved and modified via `getVelocity()` and `setVelocity()`.                                                               |
| **BoxCollider** | Defines the collision box of an entity. Stores the size (`sf::Vector2f`) and offset (`sf::Vector2f`) of the collider, along with properties: `visible` and `trigger`. Useful for collision detection. |
| **Layer** | Determines the rendering layer (`layerId`) to control draw order.                                                                                                                                     |

---

## Systems

Systems implement behavior by operating on entities that have specific Components. They apply the game logic while keeping data (Components) separate.

| System | Description |
| :--- | :--- |
| **Updater** | Updates entity Sprites based on their `Position`, `Scale`, and `Rotation` Components. Iterates over all entities with a `Sprite` Component: sets position, scale, and rotation according to their other components. This system ensures that visual representation is synchronized with the entity's data. |
| **Draw** | Renders all entities that have a Sprite Component by drawing their sf::Sprite to the window. Operates independently from the Updater; it only reads the Components and handles rendering. |

---
