## Game

The **Game** class is the central controller of the client-side application. It is responsible for initializing the window, managing the ECS (Entity Component System) World, handling user inputs, and executing the main game loop.

| Method | Signature | Description |
|:---|:---|:---|
| **Constructor** | `Game(unsigned int width, unsigned int height, const std::string& title)` | Initializes the game window with specific dimensions and title, and sets up the ECS World. |
| **Destructor** | `~Game()` | Closes the window, and destroys the game instance. |
| **Run** | `void run()` | Starts the main game loop. This method handles event polling, system updates, and rendering. |
| **Game Input** | `void gameInput(std::shared_ptr<Inputs> inputSystem)` | Processes global game inputs (e.g., pausing, quitting the game via Escape or window close event). |
| **Player Input** | `void playerInput(std::shared_ptr<Inputs> inputSystem)` | Processes inputs specific to the player entity (movement, shooting/actions). |
| **Create Camera** | `void createCamera()` | Initializes the main camera entity used to control the view and scrolling. |
| **Create Player** | `void createPlayer()` | Instantiates the player entity, assigning it necessary components like Position, Sprite, and HP. |
| **Create Bullet** | `void createBullet(int entityId)` | Creates a bullet/projectile entity starting from the position of the entity with the given `entityId`. |
| **Create Enemy** | `void createEnemy(float x, float y, int type)` | Spawns an enemy entity at the specified coordinates (`x`, `y`) with a specific behavior defined by `type`. |
| **Bullet Movement**| `void bulletMovement()` | Updates the position of all active bullets and handles memory management by destroying bullets that go off-screen. |
| **Bullet Shooting**| `void bulletShooting()` | Manages the logic for automated shooting mechanics (e.g., enemy fire patterns). |

```mermaid
classDiagram
  class Game {
    -World _world
    -sf::RenderWindow _window
    -bool _isShootKeyPressed
    +Game(width: uint, height: uint, title: string)
    +~Game()
    +run() void
    -gameInput(inputSystem: shared_ptr~Inputs~) void
    -playerInput(inputSystem: shared_ptr~Inputs~) void
    -createCamera() void
    -createPlayer() void
    -createBullet(entityId: int) void
    -createEnemy(x: float, y: float, type: int) void
    -bulletMovement() void
    -bulletShooting() void
  }