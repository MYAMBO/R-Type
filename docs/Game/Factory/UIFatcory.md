# UIFactory

The **UIFactory** is a specialized sub-factory dedicated to creating all graphical user interface elements. It handles menus, heads-up displays (HUD), and interactive settings. It works closely with the **LanguageHandler** to ensure all text elements are correctly localized.

## Integration

This factory is a core component of the main [**Factory**](Factory.md). It transforms raw data and user settings into interactive visual entities.

| Type | Name | Description |
|:---|:---|:---|
| **Context** | [`World`](../../ECS/World.md) | The ECS container where UI entities (Text, Sprites, Buttons) are created. |
| **Localization**| [`LanguageHandler`](../) | Service used to retrieve translated strings for buttons and labels. |
| **Components** | `Button`, `Text`, `GuiWidget` | Primary components used to create interactive and visual UI. |

---

## Public Methods

### Main Navigation & Screens
These methods set up full-screen interfaces for different game states.

| Method | Description |
|:---|:---|
| **createMenu** | Spawns the main menu (Play, Options, Credits, Exit). |
| **createOptionsMenu** | Spawns the settings interface including audio sliders and keybindings. |
| **createLangSelector** | Creates the language selection screen. |
| **createLoadingScreen** | Sets up the background and progress indicators for loading. |
| **createWaitingMenu** | Spawns the multiplayer lobby / waiting room interface. |
| **createGameOverScreen** / **createVictoryScreen** | Displays the end-of-game status and return-to-menu options. |

### In-Game HUD & Feedback
These methods create overlays that persist during gameplay.

| Method | Description |
|:---|:---|
| **createPlayerHUD** | Displays vital player stats (Health, Mana/Energy bars). |
| **createScoreDisplay** | Spawns the real-time score counter entity. |
| **createLevelCompanionUI** | Displays progress and level information for the player's companion. |
| **createScrapUIEmpty** | Initializes slots or placeholders for the scrap/resource collection system. |
| **createBackGameUI** | Spawns a minimal overlay (like a pause button or escape menu trigger). |

---

## Internal UI Building Logic (Private)

To maintain a consistent design, the `UIFactory` uses internal helper methods to build complex widgets:

*   **_addOptionToggle**: Creates a checkbox-style button to toggle boolean states (e.g., Fullscreen).
*   **_addOptionSlider**: Creates a draggable bar for numeric values (e.g., Volume control).
*   **_addKeyBindingRow**: Generates a label and a button that listens for key presses to remap controls.
*   **_addColorBlindCycle**: Creates a specialized button to cycle through the available accessibility color filters.

---

## Internal Structure

```mermaid
classDiagram
  class UIFactory {
    - _world: World&
    - _languageHandler: shared_ptr~LanguageHandler~
    + UIFactory(world: World&)
    + createMenu() void
    + createOptionsMenu() void
    + createPlayerHUD() void
    + createScoreDisplay() void
    - _addOptionSlider(...) void
    - _addKeyBindingRow(...) void
  }