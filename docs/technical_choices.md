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

## Technical Choices – Fail-Soft Strategy for Sprites

In our R-Type project, we decided to implement a **fail-soft approach** for sprite loading rather than crashing the game when an image file is missing or cannot be loaded.

### Motivation

- **Robustness:** The game must remain playable even if some assets are missing or incorrectly referenced.
- **Development convenience:** During asset creation or testing, missing images do not interrupt gameplay or require constant recompilation.
- **Ease of debugging:** When a texture fails to load, the system logs the error but provides a placeholder, allowing developers to continue testing other features.

### Implementation Details

- When a `Sprite` component is created, it attempts to load a texture from the provided file path.
- If the texture fails to load:
    - `_valid` is set to `false` to mark the sprite as invalid.
    - A **1×1 pixel transparent placeholder texture** is created to ensure that the `_sprite` object is never null.
- The `Draw` system checks `_valid` before applying logic that depends on the sprite's content.
- This approach prevents segmentation faults caused by dereferencing null pointers or calling `getGlobalBounds()` on an invalid sprite.

```cpp
if (!_texture.loadFromFile(filepath)) {
    std::cerr << "[Sprite] Failed to load texture: " << filepath << std::endl;
    _valid = false;
    _texture = sf::Texture({1,1});
    _sprite = std::make_shared<sf::Sprite>(_texture);
    return;
}
