## ScriptsHandler

This file declares standalone script functions designed to be attached to entities via the **Script** component. These functions encapsulate specific logic behaviors (like input handling or spawning mechanics).

| Function | Signature | Description |
|:---|:---|:---|
| **Player Input** | `void playerInput(int entityId, World &world)` | Handles the logic for controlling the player entity. It processes inputs to modify the entity's position or state. |
| **Create Bullet** | `void createBullet(int entityId, World &world)` | Logic for spawning a projectile. It creates a new bullet entity originating from the position of the source `entityId`. |
| **Background scroll** | `void backgroundScrollScript(int entityId, World &world)` | Handle logic for the scrolling background |

```mermaid
classDiagram
    +playerInput(entityId: int, world: World) void
    +createBullet(entityId: int, world: World) void
    +backgroundScrollScript(entityId: int, world: World) void
```