# GameHelper

The **GameHelper** class is a static utility class designed to assist the main game logic.  
It provides centralized helper functions to retrieve specific entities from the ECS **World** using various criteria (ID, Tag, or Group).

## Integration

This class acts as a high-level query interface to simplify entity management within systems or the main game loop.

| Type | Name | Description |
|:---|:---|:---|
| **Context** | [`World`](../../ECS/World.md) | All methods require a reference to the **World** to search through entities. |
| **Component** | [`Tag`](../../ECS/Component/Tag.md) | Used by `getEntityByTag` to identify specific entities. |
| **Component** | [`Group`](../../ECS/Component/Group.md) | Used by `getEntitiesByGroup` to filter entities by category. |

---

## Public Methods

| Method | Signature | Description |
|:---|:---|:---|
| **Get Entity By ID** | `static std::shared_ptr<Entity> getEntityById(World &world, uint64_t id)` | Retrieves a specific entity by its unique numeric identifier. Returns `nullptr` if no entity matches. |
| **Get Entity By Tag** | `static std::shared_ptr<Entity> getEntityByTag(World &world, const std::string &tag)` | Retrieves the first entity matching the specified tag string. Useful for unique entities like "Player" or "Boss". |
| **Get Entities By Group**| `static std::vector<std::shared_ptr<Entity>> getEntitiesByGroup(World &world, size_t groupId)` | Returns a list of all entities belonging to a specific logical group ID (e.g., all enemies, all bullets). |

---

## Internal Structure

As a utility class, the constructor and destructor are deleted to prevent instantiation.

```mermaid
classDiagram
  class GameHelper {
    <<static>>
    + getEntityById(world: World, id: uint64_t) shared_ptr~Entity~
    + getEntityByTag(world: World, tag: string) shared_ptr~Entity~
    + getEntitiesByGroup(world: World, groupId: size_t) vector~shared_ptr~Entity~~
  }