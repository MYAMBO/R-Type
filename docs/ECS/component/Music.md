## Music

The **Music** component handles background music streaming for an entity.  
Unlike `SoundEffect`, it streams data directly from the file to save memory. It supports pausing and resuming.

### Dependencies & Integration

SFML handles music streaming in its own internal thread. No manual threading is required.

| Type | Name | Description |
|:---|:---|:---|
| **System** | `MusicSys` | Synchronizes the actual SFML music playback with the component's `MusicState`. |

---

### Public Methods

| Method | Signature | Description |
|:------|:----------|:------------|
| **Play** | `void play();` | Requests the music to start or resume. |
| **Pause** | `void pause();` | Requests the music to pause at the current position. |
| **Stop** | `void stop();` | Requests the music to stop and reset to the beginning. |
| **Set Volume** | `void setVolume(float volume);` | Adjusts the volume (0 to 100). |
| **Set Loop** | `void setLoop(bool loop);` | Toggles whether the music should restart automatically. |

---

### Constructor

| Constructor | Signature | Description |
|:------------|:----------|:------------|
| **Music** | `Music(const std::string& filePath, float volume = 50.f, bool loop = true);` | Opens the music stream from a file path. |

---

### Internal Data

```mermaid
classDiagram
  class Music {
    -_music: sf::Music
    -_targetState: MusicState
    +play() void
    +pause() void
    +stop() void
    +setVolume(volume: float) void
    +setLoop(loop: bool) void
    +getState() MusicState
  }
  Component <|-- Music