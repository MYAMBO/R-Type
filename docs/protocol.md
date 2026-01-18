# Network Protocols Index

This document provides an overview of the network communication protocols used in the R-Type project.

## Overview

The R-Type project uses a **dual-protocol approach** for network communication:

1. **TCP Protocol** - Used for reliable, connection-oriented communication
2. **UDP Protocol** - Used for fast, real-time game state synchronization

---

## Protocol Selection

| Aspect | TCP | UDP |
|--------|-----|-----|
| **Purpose** | Authentication, session management, game initialization | Real-time gameplay, entity updates, collisions |
| **Reliability** | Guaranteed delivery | Best-effort (tolerates packet loss) |
| **Latency** | Higher (reliable but slower) | Lower (faster, optimized for real-time) |
| **Connection** | Connection-oriented | Connectionless |
| **Packet Size** | Variable | Fixed 128 bytes |

---

## Quick Links

### [TCP Protocol Documentation](TCP-protocol.md)
- **Connect Request** - Initial connection to server
- **Login** - Player authentication and username submission
- **Ready Status** - Player readiness confirmation
- **Level Selection** - Choose or upload game maps
- **Server Responses** - Connection confirmation, game start/abort signals

**When to use:** Connection setup, authentication, level selection, and game state transitions.

### [UDP Protocol Documentation](UDP-protocol.md)
- **Position Updates** - Real-time player and entity position synchronization
- **Entity Management** - Spawn, update, and despawn game entities
- **Collision Detection** - Event-driven collision notifications
- **Game Events** - Death notifications, end-game signals
- **Actions** - Player actions and commands
- **Time Synchronization** - Server clock synchronization

**When to use:** Continuous gameplay, frequent state updates, and time-sensitive interactions.

---

## Communication Flow

### Connection Establishment (TCP)
1. Client sends **Connect Request** (0x01)
2. Server responds with **Connect Response** (0x01) - assigns Player ID and UDP port
3. Client sends **Login** (0x02) with username
4. Server responds with **Login Response** (0x02)
5. Client sends **Ready** (0x03)
6. Server sends **Game Start** (0x04) when all players are ready

### Gameplay (UDP)
- Server sends **Time Synchronization** (0x08) periodically
- Client sends **Position Updates** (0x09) for player movement
- Server broadcasts **Entity Updates** (0x09) for all game objects
- Bidirectional **Actions** (0x0D) for player commands
- Server sends **Collision** (0x0A) events when entities collide
- Server sends **Dead** (0x0B) when entities are destroyed
- Server sends **End Game** (0x0C) when match concludes

---

## Key Characteristics

### TCP Protocol Features
- **Ordered delivery** of messages
- **Connection handshake** for session establishment
- **Support for level management** (selection and upload)
- **Synchronization point** before game starts

### UDP Protocol Features
- **Fixed packet size** (128 bytes) for predictable network behavior
- **Header structure** (12 bytes) with fragmentation support
- **Optional reliability** through ACK mechanism
- **Application-level fragmentation** for large messages
- **Command-based** message types with direction-dependent codes
- **Optimized for real-time** game synchronization

---

## Protocol Details Summary

### TCP Message Codes
- `0x01` - Connect Request/Response
- `0x02` - Login Request/Response
- `0x03` - Ready Status/Acknowledgment
- `0x04` - Game Start
- `0x05` - Game Abort
- `0x06` - Level Selection
- `0x07` - Upload Level

### UDP Message Codes
- `0x08` - Time Synchronization
- `0x09` - Position Update / Entity Update
- `0x0A` - Collision Event
- `0x0B` - Entity Death
- `0x0C` - Game End
- `0x0D` - Action

---

## See Also

- [TCP Protocol Documentation](TCP-protocol.md) - Detailed TCP protocol specification
- [UDP Protocol Documentation](UDP-protocol.md) - Detailed UDP protocol specification
- [Architecture Documentation](architecture.md) - Overall system architecture
- [Technical Choices](technical_choices.md) - Design decisions and rationale