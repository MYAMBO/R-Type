## ScriptsHandler

The **ScriptsHandler** file defines a collection of standalone script functions designed to be attached to entities via the [`Script`](../ECS/Component/Script.md) component.  
These functions encapsulate specific logic behaviors—such as input handling, scrolling mechanics, or visual effects—allowing them to be executed dynamically by the [`ScriptsSys`](../ECS/Systems/ScriptsSys.md) system.

### Script Functions

| Function | Signature | Description |
|:---|:---|:---|
| **Player Input** | `void playerInput(int entityId, World &world)` | Handles the logic for controlling the player entity (keyboard inputs -> position updates). |
| **Create Bullet** | `void createBullet(int entityId, World &world)` | Logic for spawning a projectile. It creates a new bullet entity originating from the position of the source `entityId`. |
| **Background Scroll** | `void backgroundScrollScript(int entityId, World &world)` | Handles the infinite scrolling logic by resetting the background's position when it moves off-screen. |
| **Player Thruster** | `void playerfire(int entityId, World &world)` | Updates the position of the "thruster fire" effect to ensure it stays attached behind the player's spaceship. |

```mermaid
<<Global Functions>>
+playerInput(entityId: int, world: World) void
+createBullet(entityId: int, world: World) void
+backgroundScrollScript(entityId: int, world: World) void
+playerfire(entityId: int, world: World) void