## Camera

The **Camera** component acts as a wrapper around the SFML View (`sf::View`).  
It defines the visible area of the game world, allowing for scrolling, zooming, and viewport management. Multiple cameras can exist, but typically one is tagged as "main_camera".

### Dependencies & Integration

This component determines how the world is rendered to the window.

| Type | Name | Description |
|:---|:---|:---|
| **System** | [`CameraSys`](../systems/CameraSys.md) | The **CameraSys** system updates the `sf::View` internal state to match the game logic. |
---

### Public Methods

| Method | Signature | Description |
|:------|:----------|:------------|
| **Get size** | `sf::Vector2f getSize() const;` | Returns the dimensions (width, height) of the visible area. |
| **Get position** | `sf::Vector2f getPosition() const;` | Returns the center position of the view in the world. |
| **Get view** | `sf::View& getView();` | Returns a mutable reference to the internal SFML View. |
| **Set size** | `void setSize(const sf::Vector2f &size);` | Updates the dimensions of the visible area (zoom level). |
| **Set position** | `void setPosition(const sf::Vector2f &position);` | Moves the camera to center on specific coordinates. |
| **Set view** | `void setView(const sf::View& view);` | Replaces the internal view with a custom configuration. |

---

### Constructor

| Constructor | Signature | Description |
|:------------|:----------|:------------|
| **Camera** | `Camera(float width, float height);` | Creates a camera with a specific viewport size. |

---

### Internal Data

```mermaid
classDiagram
  class Camera {
    - _view: sf::View
    - _size: sf::Vector2f
    - _position: sf::Vector2f
    + Camera(width: float, height: float)
    + getSize() sf::Vector2f
    + getPosition() sf::Vector2f
    + getView() sf::View&
    + setSize(size: sf::Vector2f) void
    + setPosition(position: sf::Vector2f) void
    + setView(view: sf::View&) void
  }