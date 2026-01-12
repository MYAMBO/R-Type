## GameHelper

The **GameHelper** class is a static utility class designed to assist the main game logic.  
It provides centralized helper functions to retrieve specific entities or components.

### Integration

This class acts as a high-level query interface for the **World**.

| Type | Name | Description |
|:---|:---|:---|
| **Context** | [`World`](../ECS/World.md) | All methods require a reference to the **World** to iterate over entities. |
| **Component** | [`Tag`](../ECS/Component/Tag.md) | Used by `getEntityByTag`. |
| **Component** | [`Group`](../ECS/Component/Group.md) | Used by `getEntitiesByGroup`. |

---

### Public Methods

| Method | Signature | Description |
|:---|:---|:---|
| **Get Main Camera** | `static std::shared_ptr<Camera> getMainCamera(World &world)` | Retrieves the primary camera component from the world by searching for the "main_camera" tag. |
| **Get Entity By ID** | `static std::shared_ptr<Entity> getEntityById(World &world, uint64_t id)` | Retrieves a specific entity by its unique numeric ID. Returns `nullptr` if not found. |
| **Get Entity By Tag** | `static std::shared_ptr<Entity> getEntityByTag(World &world, const std::string &tag)` | Retrieves the first entity matching the specified tag string. Returns `nullptr` if not found. |
| **Get Entities By Group**| `static std::vector<std::shared_ptr<Entity>> getEntitiesByGroup(World &world, size_t groupId)` | Returns a list of all entities belonging to a specific logical group ID. |
| **Create Basic Enemy**| `static void createBasicEnemy(World &world, float x, float y)` | Spawns a standard enemy entity at the specified `(x, y)` coordinates with default components. |

---

### Internal Structure

```mermaid
classDiagram
  class GameHelper {
    <<static>>
    + getMainCamera(world: World) shared_ptr~Camera~
    + getEntityById(world: World, id: uint64_t) shared_ptr~Entity~
    + getEntityByTag(world: World, tag: string) shared_ptr~Entity~
    + getEntitiesByGroup(world: World, groupId: size_t) vector~shared_ptr~Entity~~
    + createBasicEnemy(world: World, x: float, y: float) void
  }