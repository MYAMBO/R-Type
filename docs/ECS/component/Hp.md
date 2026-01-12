## HP

The **HP** (Health Points) component store the vitality of an entity.  
It tracks the current health, the maximum health capacity, and the living state of the entity. It is the primary component used to determine if an entity should be destroyed or triggered as "dead".

### Dependencies & Integration

This component is usually modified by collision or game logic systems.

| Type | Name | Description |
|:---|:---|:---|
| **System** | [`Collision`](../systems/Collision.md) | The **Collision** system often reduces the **HP** value when an entity collides with another entity possessing a [`Damage`](Damage.md) component. |

---

### Public Methods

| Method | Signature | Description |
|:------|:----------|:------------|
| **Get HP** | `unsigned int getHP() const;` | Returns the current amount of health points. |
| **Get Max HP** | `unsigned int getMaxHP() const;` | Returns the maximum health capacity. |
| **Get Alive State** | `bool isAlive() const;` | Returns `true` if the entity is considered alive (usually HP > 0), `false` otherwise. |
| **Set HP** | `void setHP(unsigned int hp);` | Updates the current health value. |
| **Set Max HP** | `void setMaxHP(unsigned int maxHp);` | Updates the maximum health capacity. |
| **Set Alive State** | `void setAlive(bool alive);` | Manually updates the living state (useful for respawning or instant death). |

---

### Constructor

| Constructor | Signature | Description |
|:------------|:----------|:------------|
| **HP** | `explicit HP(unsigned int hp);` | Initializes the component with a specific health value. Sets both current and max HP to this value. |

---

### Internal Data

```mermaid
classDiagram
  class HP {
    - _hp: unsigned int
    - _maxHp: unsigned int
    + HP(hp: uint)
    + getHP() uint
    + getMaxHP() uint
    + isAlive() bool
    + setHP(hp: uint) void
    + setMaxHP(maxHp: uint) void
    + setAlive(alive: bool) void
  }