## Scale Collider

The Scale component can modify the collider

| Method | Signature | Description |
| :--- | :--- | :--- |
| **Get Scale** | `float getScale() const` | Returns the current scale of the collider. |
| **Set Scale** | `void setScale(float scale)` | Update the scale of the collider. |

```mermaid
classDiagram
  class ScaleCollider {
    _scale: float
  }
```