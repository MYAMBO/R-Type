# Scripts

The **Scripts** header defines a collection of standalone logic functions designed to be attached to entities via the [`Script`](../../ECS/Component/Script.md) component.  
These functions encapsulate specific behaviors—ranging from gameplay mechanics and UI logic to complex visual sequences—and are executed dynamically by the [`ScriptsSys`](../../ECS/Systems/ScriptsSys.md).

## Integration

Each script follows a standard signature: `void (int entityId, World& world)`. This allows the script to access the entity's components and the global world state.

| Type | Name | Description |
|:---|:---|:---|
| **System** | [`ScriptsSys`](../../ECS/Systems/ScriptsSys.md) | Iterates over entities with a `Script` component and calls these functions. |
| **Component** | [`Script`](../../ECS/Component/Script.md) | Stores the function pointer to one of the scripts below. |

---

## Script Categories

### Gameplay & Actors
Logic governing the behavior of active game entities.

| Function | Description |
|:---|:---|
| **playerScript** | Handles local player logic (movement constraints, state updates). |
| **playerfire** | Manages the thruster fire effect/positioning relative to the player. |
| **enemyScript** | Defines AI movement patterns or automated shooting for enemies. |
| **companionScript** | Controls the support drone behavior following the player. |
| **companionLaserScript** | Logic for the companion's attack patterns. |

### Settings & Meta Logic
Logic for managing global states, options, and persistence.

| Function | Description |
|:---|:---|
| **volumeSettingsScript** | Reacts to changes in the "volume" data entity to update audio systems. |
| **availabilitySettingsScript** | Handles accessibility toggles (colorblind modes, dyslexia fonts). |
| **changeSceneScript** | Logic triggered to transition between different [SceneTypes](Game.md). |
| **refreshCaches** | Utility script to force update internal system caches. |

### Visuals & Cinematic Sequences
Scripts dedicated to eye-candy, transitions, and the "Kayu/Myambo" sequences.

| Function | Description |
|:---|:---|
| **backgroundScrollScript** | Handles infinite parallax scrolling for the game background. |
| **sparkScript** | Manages the lifetime and movement of particle effects. |
| **hpBarScript** | Dynamically scales the HP bar sprite based on the entity's health. |
| **creditsScript** / **creditsNameScript** | Logic for scrolling text and names during the credit sequence. |
| **kayuScript** / **myamboScript** | Main logic for the specific animated sequences (Intro/Easter eggs). |
| **glowScripts** | (*kayuGlow*, *myamboGlow*, etc.) Handles pulsing or glowing visual effects. |

---

## Internal Structure

These scripts are not part of a class; they are global functions to minimize overhead and allow for easy assignment to component function pointers.

