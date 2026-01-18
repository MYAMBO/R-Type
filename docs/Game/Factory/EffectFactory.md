# EffectFactory

The **EffectFactory** is a specialized sub-factory responsible for creating non-gameplay visual entities. This includes special cinematic-like sequences (Easter eggs or intro/outro screens) and transient visual effects like particle systems.

## Integration

This factory is instantiated and used by the main [**Factory**](Factory.md) to separate visual "flavor" from core gameplay logic.

| Type | Name | Description |
|:---|:---|:---|
| **Context** | [`World`](../../ECS/World.md) | A reference to the ECS World where entities are spawned. |
| **Dependency** | [`SceneType`](../Game.md) | Used to assign effects to specific game states. |

---

## Public Methods

### Special Sequences
These methods initialize entities and scripts for specific "flavor" scenes in the game.

| Method | Signature | Description |
|:---|:---|:---|
| **Create Kayu** | `void createKayu()` | Spawns the visual entities and logic for the "Kayu" sequence. |
| **Create Myambo** | `void createMyambo()` | Spawns the visual entities and logic for the "Myambo" sequence. |
| **Create Credits** | `void createCredits()` | Sets up the scrolling text and background elements for the credits scene. |

### Visual Effects (VFX)

| Method | Signature | Description |
|:---|:---|:---|
| **Create Sparks** | `static void createSparks(World &world, float x, float y, int amount, SceneType scene, int lifeTime)` | **Static Utility**: Spawns a specified number of spark particles at `(x, y)`. Particles are automatically cleaned up after `lifeTime` (default: 300ms). |

---

## Internal Logic

Most effects created by this factory utilize a combination of the following components:
*   **Sprite / Animator**: For the visual representation.
*   **Velocity**: For moving particles or scrolling credits.
*   **Script**: To handle life-time expiration or custom movement patterns (e.g., the Kayu animation).

### Particle System (Sparks)
The `createSparks` method is static, allowing it to be called from anywhere (like collision systems or death handlers) without needing a Factory instance, as long as a reference to the `World` is provided.

```mermaid
classDiagram
  class EffectFactory {
    - _world: World&
    + EffectFactory(world: World&)
    + createKayu() void
    + createMyambo() void
    + createCredits() void
    + createSparks(world, x, y, amount, scene, lifeTime) static void
  }