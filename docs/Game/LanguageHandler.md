# LanguageHandler

The **LanguageHandler** class is a utility responsible for managing the game's localization. It loads translation data from external files and provides a centralized way to retrieve strings associated with specific keys (e.g., translating "PLAY_BUTTON" to "Jouer" or "Play").

## Integration

The `LanguageHandler` is primarily used by the [**UIFactory**](Factory/UIFactory.md) to ensure that every text element displayed on the screen matches the user's selected language.

| Type | Name | Description |
|:---|:---|:---|
| **Storage** | `std::unordered_map` | Stores the key-value pairs of the currently loaded language for fast retrieval. |
| **Error Handling**| `LoadLanguageException` | Custom exception thrown when a language file cannot be found or parsed. |

---

## Public Methods

| Method | Signature | Description |
|:---|:---|:---|
| **Constructor** | `LanguageHandler(const string &langId)` | Initializes the handler and immediately attempts to load the language specified by `langId`. |
| **Load Language** | `void loadLanguageFile(const string &langId)` | Clears the current translations and loads a new set from the corresponding language file (e.g., `en.json`). |
| **Get Translation** | `string getTranslation(const string &key)` | Returns the translated string for the given key. If the key is not found, it usually returns the key itself or an empty string. |

---

## Error Handling

The class defines a specific nested exception:
*   **LoadLanguageException**: This is triggered during `loadLanguageFile` if:
    *   The file does not exist in the assets folder.
    *   The file format is invalid (corrupted JSON/text).
    *   Read permissions are missing.


## Internal Structure

```mermaid
classDiagram
  class LanguageHandler {
    - _language: unordered_map~string, string~
    + LanguageHandler(languageId: string)
    + loadLanguageFile(languageId: string) void
    + getTranslation(key: string) string
  }

  class LoadLanguageException {
    + what() const char*
  }
