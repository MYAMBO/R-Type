# WorldFactory

The **WorldFactory** is a specialized sub-factory responsible for instantiating all gameplay-related entities. It handles the creation of players, enemies, projectiles, and environmental objects. This factory is the primary bridge between the network data (entity IDs and types) and the ECS components.

## Integration

This factory is managed by the main [**Factory**](Factory.md) and focuses on entities that possess physical properties (Position, Velocity, Collisions) and gameplay logic.

| Type | Name | Description |
|:---|:---|:---|
| **Context** | [`World`](../../ECS/World.md) | The ECS container where gameplay entities are registered. |
| **Logic** | Network Sync | Many methods take an `entityId` provided by the server to ensure client-server consistency. |
| **Physics** | Components | Frequently attaches `Position`, `Velocity`, `BoxCollider`, and `Damage`. |

---

## Public Methods

### Core Entities
These methods create the primary actors of the game world.

| Method | Signature | Description |
|:---|:---|:---|
| **Create Player** | `createPlayer(id, x, y)` | Spawns a player entity. Attaches controls, health, and player-specific sprites. |
| **Create Enemy** | `createEnemy(x, y, type, id)` | Spawns an enemy of a specific type (Basic, Fast, Tank, etc.) at the given coordinates. |
| **Create Companion**| `createCompanion(playerId)` | Spawns a support drone/companion linked to a specific player ID. |

### Projectiles & Combat
Methods dedicated to the offensive elements of the game.

| Method | Signature | Description |
|:---|:---|:---|
| **Player Bullet** | `createBullet(id, x, y, type)` | Spawns a projectile fired by a player. |
| **Enemy Bullet** | `createEnemyBullet(id, x, y)` | Spawns a standard projectile fired by an enemy. |
| **Special Bullet** | `createBackwardEnemyBullet(...)` | Spawns specific projectile patterns (e.g., firing behind). |
| **Companion Laser**| `createLasersCompanion(...)` | Handles the specific attack logic and visuals for the player's companion. |

### Environment & Progression
Entities that handle world setup and rewards.

| Method | Signature | Description |
|:---|:---|:---|
| **Create Camera** | `createCamera()` | Spawns the camera entity, essential for the [**CameraSystem**](../../ECS/System/CameraSystem.md). |
| **Create PowerUp** | `createPowerUp(x, y, type, id)` | Spawns collectible items (Heal, Speed, etc.). |
| **Create Scraps** | `createScraps(world, x, y)` | Spawns resource materials dropped by enemies. |
| **Create Scrap UI** | `createScrapUI(world, index)` | Creates world-space or linked UI elements to track collected resources. |
| **Gameplay Music**| `createMusicGameplay()` | Spawns the entity responsible for the background audio track of the level. |


```mermaid
classDiagram
  class WorldFactory {
    - _world: World&
    + createPlayer(playerId: uint64, x: float, y: float) void
    + createEnemy(x: float, y: float, type: int, id: int) void
    + createBullet(id: size_t, x: int, y: int, type: int) void
    + createCamera() void
    + createPowerUp(x: float, y: float, type: int, id: int) void
  }