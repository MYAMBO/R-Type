# Factory

The **Factory** class acts as a central Facade for entity creation. Instead of manually assembling ECS components throughout the code, the `Factory` provides a high-level API to spawn complex objects (players, enemies, UI menus, visual effects).

Internally, it orchestrates four specialized sub-factories to keep the codebase modular and maintainable.

## Sub-Factories

The `Factory` delegates its tasks to these specific modules:

| Sub-Factory | Responsibility |
|:---|:---|
| `UIFactory` | Menus, HUD, buttons, and interface elements. |
| `WorldFactory` | Gameplay entities: players, enemies, bullets, and cameras. |
| `EffectFactory` | Visual effects, particles (sparks), and special scenes (Credits). |
| `ToolsFactory` | Utility entities and technical game tools. |

---

## Public Methods

### Scene & UI Creation
These methods typically delegate to `UIFactory` or `EffectFactory`.

| Method | Description |
|:---|:---|
| `createMenu()` / `createWaitingMenu()` | Initializes the main menu or the multiplayer waiting room. |
| `createOptionsMenu()` / `createLevelSelect()` | Spawns the settings or level selection interfaces. |
| `createLoadingScreen()` | Sets up the visual assets for the loading transition. |
| `createGameOverScreen()` / `createVictoryScreen()` | Displays the end-game state interfaces. |
| `createCredits()` / `createKayu()` / `createMyambo()` | Spawns specific visual/special sequence entities. |

### Gameplay Entities
These methods typically delegate to `WorldFactory`.

| Method | Description |
|:---|:---|
| `createPlayer(id, x, y)` | Spawns a player entity with its components (Position, Velocity, Sprite, etc.). |
| `createEnemy(x, y, type, id)` | Spawns a networked enemy based on the type received from the server. |
| `createBullet(...)` | Handles both player and enemy projectile instantiation. |
| `createPowerUp(x, y, type, id)` | Spawns collectible items. |
| `createCompanion(playerId)` | Spawns the support drone associated with a player. |
| `createCamera()` | Initializes the main viewing camera for the world. |

### Feedback & HUD
| Method | Description |
|:---|:---|
| `createPlayerHUD()` / `createScoreDisplay()` | Initializes the in-game heads-up display. |
| `createSparks(world, x, y, ...)` | Generates particle effects at a specific location. |
| `createScraps(...)` | Spawns resource entities in the world. |

---

## Internal Logic

The `Factory` does not contain the logic for adding components itself. It serves as a router. For example, when `createEnemy` is called:

1.  `Game` calls `_factory.createEnemy(...)`.
2.  `Factory` calls `_worldFactory.createEnemy(...)`.
3.  `WorldFactory` attaches `Position`, `Health`, `Sprite`, `BoxCollider`, etc., to a new entity in the `World`.

```mermaid
classDiagram
  class Factory {
    - _uiFactory: UIFactory
    - _worldFactory: WorldFactory
    - _effectFactory: EffectFactory
    - _toolsFactory: ToolsFactory
    + createPlayer(id, x, y) void
    + createEnemy(x, y, type, id) void
    + createMenu() void
    + createSparks(world, x, y, amount, scene) void
    + createGameOverScreen() void
  }
  ```