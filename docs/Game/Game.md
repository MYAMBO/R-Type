# Game Class

The **Game** class is the central controller of the client-side application.  
It coordinates the main game loop, manages the ECS **World**, handles networking synchronization via **IGameNetwork**, and delegates entity creation to the **Factory**. It also manages scene transitions (Menu, Gameplay, Pause, etc.) and movement interpolation.

## Enums

The class defines several enumerations to standardize game constants:
*   **LayerType**: Defines rendering order (`BACKGROUND = -1`, `UI = 1000`).
*   **SceneType**: Defines the current state of the application (`MENU`, `GAMEPLAY`, `LOADING`, `PAUSE`, `GAME_OVER`, `VICTORY`, etc.).
*   **PlayerColor**: Defines available player skin variants (`BLUE`, `PURPLE`, `RED`, `GREEN`).

## Dependencies & Integration

| Type | Name | Description |
|:---|:---|:---|
| **Manager** | [`World`](../ECS/World.md) | The ECS container managed by the Game. |
| **Factory** | [`Factory`](../Factory/Factory.md) | Handles the instantiation of complex entities. |
| **Interface** | [`IGameNetwork`](../Core/IGameNetwork.md) | Abstract interface for communicating with the server. |

---

## Public Methods

| Method | Signature | Description |
|:---|:---|:---|
| **Constructor** | `Game(IGameNetwork& network, uint width, uint height, string title)` | Initializes the window, ECS, and Factory. Inject the network interface. |
| **Run** | `void run()` | Starts the main game loop (Events -> Network Sync -> Update -> Render). |
| **Update Entity** | `void updateEntity(uint32_t id, uint16_t type, float x, float y)` | Synchronizes or spawns an entity based on server data. |
| **Handle Action** | `void handleAction(uint32_t id, uint8_t action, uint32_t data)` | Processes specific actions (animations, status changes) sent by the server. |
| **Kill Entity** | `int killEntity(int id)` | Removes an entity from the world based on its ID. |
| **Mana Update** | `void updatePlayerMana(uint32_t playerId, int mana)` | Updates the specific mana/resource component of a player. |
| **Scene Logic** | `void menudisplay()` / `void gameplaydisplay()` | Specific logic for rendering and updating the Menu and Gameplay scenes. |
| **End Screen** | `void showEndScreen(uint8_t status)` | Displays victory or defeat screens based on the status code. |

## Private Internal Logic

| Method | Signature | Description |
|:---|:---|:---|
| **Game Input** | `void gameInput(shared_ptr<Inputs> inputSystem)` | Handles global window inputs and scene-independent controls. |
| **Player Input** | `void playerInput(uint32_t entityId, World &world)` | Processes local player inputs and sends move/action commands to the server. |
| **Interpolation** | `void smootherMovement(int entityId, World &world, float tX, float tY)` | Smoothly moves a networked entity towards its target position to hide latency. |
| **Persistence** | `void savefile()` / `void loadfile()` | Handles local data storage (settings, progress). |
| **Heal** | `void healEntity(uint32_t entityId, uint32_t amount)` | Applies healing logic to a specific entity. |

---

## Internal Data

```mermaid
classDiagram
  class Game {
    - _window: sf::RenderWindow
    - _world: World
    - _network: IGameNetwork&
    - _factory: Factory
    - _musicVolume: int
    - _sfxVolume: int
    - _isShootKeyPressed: bool
    + Game(network: IGameNetwork&, width: uint, height: uint, title: string)
    + ~Game()
    + run() void
    + updateEntity(id: uint32_t, type: uint16_t, x: float, y: float) void
    + handleAction(id: uint32_t, action: uint8_t, data: uint32_t) void
    + killEntity(id: int) int
    + showEndScreen(status: uint8_t) void
    - gameInput(inputSystem: shared_ptr~Inputs~) void
    - playerInput(entityId: uint32_t, world: World) void
    - smootherMovement(entityId: int, world: World, targetX: float, targetY: float) void
    - savefile() void
    - loadfile() void
  }