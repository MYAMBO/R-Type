## Audio System

The **Audio** system is responsible for managing all auditory feedback in the game. It processes two distinct types of audio: **Sound Effects** (short, sounds played in separate threads) and **Music** (long, streamed background tracks with state management).

### Dependencies & Integration

This system orchestrates the audio components and synchronizes them with the game's current state.

| Type | Name | Description |
|:---|:---|:---|
| **Component** | [`SoundEffect`](../component/SoundEffect.md) | Used for "fire-and-forget" sounds like shots or explosions. |
| **Component** | [`Music`](../component/Music.md) | Used for persistent background music that can be paused or stopped. |
| **Component** | [`Scene`](../component/Scene.md) | Ensures that sound effects are only triggered if they belong to the active scene. |
| **Context** | `World` | Accesses the current active scene ID and the global delta time. |

---

### Public Methods

| Method | Signature | Description |
|:------|:----------|:------------|
| **Update** | `void update(const float& dt, World &w) override;` | Processes all audio components. It triggers new sound effects and synchronizes music playback based on their target states. |

---

### Internal Logic

#### 1. Sound Effects (Polyphony)
The system iterates through all `SoundEffect` components. If a component's state is `PLAYING` and it belongs to the current `Scene`:
*   The state is immediately reset to `STOPPED` to prevent re-triggering.
*   A **detached thread** is spawned to handle the playback. This allows multiple instances of the same sound to overlap (polyphony) without blocking the main game loop.
*   The thread remains alive until the SFML sound finishes playing.

#### 2. Music (State Management)
The system iterates through all `Music` components and synchronizes the underlying `sf::Music` object with the component's `MusicState`:
*   **PLAYING**: Starts or resumes the music stream.
*   **PAUSED**: Suspends playback while maintaining the current position.
*   **STOPPED**: Stops playback and rewinds to the beginning.

---

### Internal Data

```mermaid
classDiagram
  class Audio {
    +update(dt: float, w: World) void
  }
  class System {
    <<Interface>>
  }
  System <|-- Audio
  Audio ..> SoundEffect : Spawns Threads
  Audio ..> Music : Syncs State
  Audio ..> Scene : Filters by