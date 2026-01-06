## Game

The **Game** class is the central controller of the client-side application.  
It coordinates the main game loop, manages the ECS **World**, handles networking synchronization via **IGameNetwork**, and delegates entity creation to the **Creator**. It also handles input processing and movement interpolation.

### Enums

The class defines several enumerations to standardize game constants:
*   **LayerType**: Defines rendering order (`BACKGROUND = -1`, `UI = 1000`).
*   **PlayerColor**: Defines available player skin variants (`BLUE`, `PURPLE`, `RED`, `GREEN`).
*   **entitiesType**: Defines identifiers for network spawning (`None`, `Player`, `Enemy`, `Bullet`).

### Dependencies & Integration

| Type | Name | Description |
|:---|:---|:---|
| **Manager** | [`World`](../ECS/World.md) | The ECS container managed by the Game. |
| **Factory** | [`Creator`](../Creator/Creator.md) | Handles the instantiation of complex entities. |
| **Interface** | [`IGameNetwork`](../Core/IGameNetwork.md) | Abstract interface for communicating with the server (UDP/TCP). |

---

### Public Methods

| Method | Signature | Description |
|:---|:---|:---|
| **Constructor** | `Game(IGameNetwork& network, uint width, uint height, string title)` | Initializes the window, ECS, and Entity Creator. Inject the network interface. |
| **Destructor** | `~Game()` | Cleans up resources and closes the window. |
| **Run** | `void run()` | Starts the main game loop (Poll Events -> Network Sync -> Update -> Render). |
| **Kill Entity** | `int killEntity(int id)` | Removes an entity from the world based on its ID. Returns status. |
| **Handle Spawn** | `void handleSpawn(int id, int type, float x, float y)` | Called by the network when an entity needs to be created on the client side. |
| **Scene Logic** | `void menudisplay()`<br>`void gameplaydisplay()` | Specific logic loops or update calls for the Menu and Gameplay scenes. |

### Private Internal Logic

| Method | Signature | Description |
|:---|:---|:---|
| **Game Input** | `void gameInput(std::shared_ptr<Inputs> inputSystem)` | Handles global inputs (window closing, escape key). |
| **Player Input** | `void playerInput(int entityId, World &world)` | Processes local player inputs and sends move commands to the server. |
| **Loading** | `void updateLoadingState(float progress, string status)` | Updates the visual representation of the loading screen. |
| **Interpolation** | `void smootherMovement(int entityId, World &world, float tX, float tY)` | Smoothly moves a networked entity towards its target position (`tX`, `tY`) to hide network latency. |
| **Shooting** | `void bulletShooting()` | Manages logic for automated shooting or bullet patterns. |

---

### Internal Data

```mermaid
classDiagram
  class Game {
    - _window: sf::RenderWindow
    - _world: World
    - _network: IGameNetwork&
    - _creator: Creator
    - _isShootKeyPressed: bool
    + Game(network: IGameNetwork&, width: uint, height: uint, title: string)
    + ~Game()
    + run() void
    + killEntity(id: int) int
    + handleSpawn(id: int, type: int, x: float, y: float) void
    + menudisplay() void
    + gameplaydisplay() void
    - gameInput(inputSystem: shared_ptr~Inputs~) void
    - playerInput(entityId: int, world: World) void
    - updateLoadingState(progress: float, status: string) void
    - smootherMovement(entityId: int, world: World, targetX: float, targetY: float) void
    - bulletShooting() void
  }