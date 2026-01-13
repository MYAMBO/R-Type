## LevelLoader

The **LevelLoader** class is responsible for loading game levels from JSON files.  
It parses configuration data (metadata, entities) and instantiates the corresponding entities into the **World** using high-level helper utilities.

This design helps keep level parsing logic separate from entity creation logic.

---

## Integration

This class acts as a bridge between JSON level files and the ECS architecture.

| Type | Name | Description |
|:---|:---|:---|
| **Context** | [`World`](../ECS/World.md) | ECS world where level entities are instantiated. |
| **Utility** | [`GameHelper`](./GameHelper.md) | Used to create game entities (e.g. enemies). |
| **Library** | `nlohmann::json` | Library used to parse JSON level files. |
| **Input** | `std::ifstream` | Reads level files from disk. |

---

## JSON Level Format

Level files must follow the structure below:

```json
{
  "metadata": {
    "name": "Level 1"
  },
  "entities": [
    {
      "type": "enemy",
      "x": 100,
      "y": 200
    }
  ]
}
