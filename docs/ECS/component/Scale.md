## Scale

The **Scale** component defines the resizing factor of an entity.  
It stores a uniform multiplier (float) that scales the entity's visual representation (Sprite) to be larger (> 1.0) or smaller (< 1.0).

### Dependencies & Integration

This component is primarily used by the rendering system to adjust the size of the sprite.

| Type | Name | Description |
|:---|:---|:---|
| **System** | [`Draw`](../systems/Draw.md) | The **Draw** system retrieves the scale factor and applies it to the `sf::Sprite` (via `setScale`) before rendering. |

---

### Public Methods

| Method | Signature | Description |
|:------|:----------|:------------|
| **Get Scale** | `float getScale() const;` | Returns the current uniform scale factor. |
| **Set Scale** | `void setScale(float scale);` | Updates the scale factor. |

---

### Constructor

| Constructor | Signature | Description |
|:------------|:----------|:------------|
| **Scale** | `explicit Scale(float scale = 1.0f);` | Initializes the component with a specific scale factor (default is 1.0f, meaning original size). |

---

### Internal Data

```mermaid
classDiagram
  class Scale {
    - _scale: float
    - _type: std::string
    + Scale(scale: float)
    + getScale() float
    + setScale(scale: float) void
  }
  Component <|-- Scale