## Game

The **Game** class is the central controller of the client-side application. It is responsible for initializing the window, managing the ECS (Entity Component System) World, handling global inputs, and executing the main game loop.

### LayerType Enum
Defines the rendering order for entities:
*   `BACKGROUND` (-1)
*   `UI` (1000)

### Class Reference

| Method | Signature | Description |
|:---|:---|:---|
| **Constructor** | `Game(unsigned int width, unsigned int height, const std::string& title)` | Initializes the game window with specific dimensions and title, and sets up the ECS World. |
| **Run** | `void run()` | Starts the main game loop. This method handles event polling, system updates, and rendering. |
| **Game Input** | `void gameInput(std::shared_ptr<Inputs> inputSystem)` | Processes global game inputs (e.g., pausing, quitting the game via Escape or window close event). |
| **Create Camera** | `void createCamera()` | Initializes the main camera entity used to control the view. |
| **Create Player** | `void createPlayer()` | Instantiates the player entity, assigning it necessary components like Position, Sprite, etc. |
| **Create Enemy** | `void createEnemy(float x, float y, int type)` | Spawns an enemy entity at the specified coordinates (`x`, `y`) based on the given `type`. |
| **Bullet Shooting**| `void bulletShooting()` | Manages the logic for automated shooting mechanics (e.g., enemy fire patterns). |

```mermaid
classDiagram
  class Game {
    -World _world
    -sf::RenderWindow _window
    +Game(width: uint, height: uint, title: string)
    +run() void
    -gameInput(inputSystem: shared_ptr~Inputs~) void
    -createCamera() void
    -createPlayer() void
    -createEnemy(x: float, y: float, type: int) void
    -bulletShooting() void
  }