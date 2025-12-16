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

## Network

| Criteria | SFML:Network | ENet | Boost.Asio |
|----------|:------------:|:----:|:----------:|
| **TCP Support** | + | - | + |
| **UDP Support** | + | + | + |
| **Reliable UDP** | - | + | - |
| **Multiplatform** | + | + | + |
| **Simplicity** | + | + | - |
| **Lightweight** | + | + | - |
| **Already Integrated** | + | - | - |
| **HTTP/FTP Clients** | + | - | - |
| **Setup Time** | + | + | - |
| **Game-Oriented** | + | + | - |
| **Learning Curve** | + (none) | - (new API) | - (complex) |

We choose to use SFML:Network due to its native support for both TCP and UDP protocols, which makes it better than ENet that only supports UDP and lacks any TCP functionality. This dual-protocol support allows us to handle login systems, chat, and file transfers over TCP while using UDP for real-time game updates.

Additionally, SFML:Network stands out for its simplicity and code readability compared to Boost.Asio, which requires extensive boilerplate code and has a steep learning curve. SFML was designed with game developers in mind, offering clean and intuitive functions that take minutes to learn rather than hours, making our codebase more maintainable in the long term.

Another key advantage is the seamless integration with our existing project. Adding ENet or Boost.Asio would introduce new dependencies, new APIs to learn, and potential compatibility issues. Since we already use SFML for graphics and audio, the networking module fits naturally into our workflow without any additional setup or context-switching between different library conventions.

Furthermore, SFML:Network is fully multiplatform, running on Windows, Linux, and macOS without any code changes. This cross-platform compatibility, combined with its lightweight nature and minimal dependencies, keeps our project lean and portable. In contrast, Boost.Asio brings a heavy dependency chain and complex configuration requirements that can complicate cross-platform builds.

We acknowledge that SFML:Network lacks reliable UDP, which ENet provides. However, this trade-off is acceptable because our game does not require the millisecond-level latency optimization that reliable UDP offers. For our use case, standard TCP and UDP protocols work perfectly fine, and the benefits of simplicity, integration, multiplatform support, and dual-protocol support outweigh the need for reliable UDP.
