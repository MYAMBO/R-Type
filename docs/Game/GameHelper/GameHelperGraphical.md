# GameHelperGraphical

The **GameHelperGraphical** class is a static utility class dedicated to visual, graphical, and audio helpers. It complements the logic-oriented `GameHelper` by providing tools for color manipulation, camera retrieval, and complex graphical entity instantiation (particles, enemies with sprites, animations).

## Accessibility & Colors

The class provides built-in support for color blindness through transformation matrices.

*   **ColorBlindMode**: Enum defining modes like `Protanopia`, `Deuteranopia`, `Tritanopia`, and `Achromatopsia`.
*   **ColorMatrix**: A structure representing a 3x3 matrix used to shift RGB values.
*   **ColorFilters**: A predefined map containing the mathematical constants for each accessibility mode.

## Public Methods

### Visual & Camera Utilities

| Method | Signature | Description |
|:---|:---|:---|
| **Hue to RGB** | `static sf::Color hueToRGB(float hue)` | Converts a hue value to an SFML Color object. |
| **Get Matrix** | `static ColorMatrix getColorMatrix(ColorBlindMode mode)` | Returns the corresponding transformation matrix for a specific color blindness mode. |
| **Get Main Camera** | `static std::shared_ptr<Camera> getMainCamera(World &world)` | Retrieves the primary camera entity from the world. |

### Environment & FX

| Method | Signature | Description |
|:---|:---|:---|
| **Star Field** | `static void createStarField(World &world)` | Initializes the background star layer. |
| **Create Sparks** | `static void createSparks(World &world, float x, float y, int amount)` | Spawns a cluster of particle entities at a specific location. |
| **Ambiance** | `static void playRandomAmbianceEnemy(World &world)` | Triggers random ambient sounds or visual cues. |
| **Reset Credits** | `static void resetCreditsPositions(World &world)` | Resets the scrolling position of credit entities. |

### Entity Spawning (Graphical)

These methods handle the creation of entities with their associated visual components (Sprites, Animators).

| Method | Signature | Description |
|:---|:---|:---|
| **Enemy Spawners** | `createBasicEnemy`, `createFastEnemy`, `createTankEnemy`, `createSinusEnemy`, `createShootingEnemy` | Creates specific enemy types with their respective textures and animations. |
| **Boss / Special** | `createPortalBoss`, `createWarningPortal` | Handles complex multi-component entities for boss encounters. |
| **Power-Ups** | `createHealPowerUp` | Spawns collectible items with visual feedback. |
| **GUI** | `createScoreGUI(World &world, float x, float y, string text)` | Instantiates a text-based interface element for scoring. |

### Audio & Animation

| Method | Signature | Description |
|:---|:---|:---|
| **Sound Effect** | `static void soundEffectEntity(...)` | Creates an ephemeral entity that plays a sound effect at a specific volume and scene. |
| **Animator** | `static void createAnimatorEntity(...)` | Creates a generic entity with a sprite sheet animator (handles rows, cols, and speed). |

---

## Internal Structure

```mermaid
classDiagram
  class GameHelperGraphical {
    <<static>>
    + hueToRGB(hue: float) sfColor
    + getColorMatrix(mode: ColorBlindMode) ColorMatrix
    + getMainCamera(world: World) shared_ptr~Camera~
    + createStarField(world: World) void
    + createSparks(world: World, x: float, y: float, amount: int) void
    + createAnimatorEntity(world: World, ...) void
    + soundEffectEntity(path: string, volume: float, scene: int, world: World) void
  }