# Packet System Documentation

## Overview

The R-Type packet system provides a robust communication protocol for exchanging data between the client and server over UDP. It uses a custom header-based packet structure with opcode-based commands to handle various game events like entity updates, collisions, player actions, and game state changes.

---

## Architecture

### Packet Structure

The packet system consists of three main components:

1. **UDP Header** - Fixed 12-byte header containing metadata
2. **Payload** - Variable-length data containing opcodes and command-specific information
3. **Packet Builder** - Helper class for constructing and sending packets

#### UDP Header Format

[ID (4 bytes)] [ACK (4 bytes)] [PacketNbr (1 byte)] [TotalPacketNbr (1 byte)] [DataSize (2 bytes)]

| Field | Size | Purpose |
|-------|------|---------|
| **ID** | 4 bytes | Identifies the entity/player sending the packet |
| **ACK** | 4 bytes | Acknowledgment flag or counter for packet ordering |
| **PacketNbr** | 1 byte | Current packet number in a sequence |
| **TotalPacketNbr** | 1 byte | Total number of packets in the sequence |
| **DataSize** | 2 bytes | Size of the payload data in bytes |

**Constraints:**
- Maximum payload size: 116 bytes
- Header size: 12 bytes
- Total maximum packet size: 128 bytes

### Packet Building

Packets are built using the `Packet` class, which uses a builder pattern with method chaining for easy construction:
```
cpp
Packet packet;
packet.setId(playerId)
.setAck(0)
.setPacketNbr(1)
.setTotalPacketNbr(1)
.updatePosition(entityId, x, y);
```
---

## Opcodes and Commands

Opcodes are single-byte identifiers that specify the type of command being sent. Each opcode has a specific payload format.

### 0x08 - Time Synchronization

**Purpose:** Synchronize game time between client and server

**Payload Format:**
```

[Opcode: 0x08] [Time (4 bytes)]
```
**Parameters:**
- `time` (uint32_t) - Current server time in milliseconds

**Usage:**
```cpp
packet.timeSync(serverTime);
```
```


---

### 0x09 - Position Update / Entity Spawn

**Purpose:** Update entity position or spawn a new entity

**Payload Format:**
```
[Opcode: 0x09] [Entity ID (4 bytes)] [Type (2 bytes)] [X (4 bytes)] [Y (4 bytes)]



**Parameters:**
- `id` (uint32_t) - Unique identifier of the entity
- `type` (uint16_t) - Entity type (0 = position update, non-zero = spawn)
- `x` (float) - X coordinate
- `y` (float) - Y coordinate

**Entity Types:**
- `0` - Position update for existing entity
- `1` - Player
- `2` - Fast enemy
- `3` - Tank enemy
- `4` - Sinus enemy
- `5` - Shooting enemy
- `6` - Portal boss
- `7` - Portal
- `8` - Bullet
- `9` - Enemy bullet
- `10` - Backward enemy bullet
- `11` - Heal powerup

**Usage:**
```c++
// Position update
packet.updatePosition(playerId, 100.0f, 200.0f);

// Spawn entity
packet.Spawn(enemyId, 2, 300.0f, 150.0f);
```


---

### 0x0A - Collision Event

**Purpose:** Report a collision between two entities

**Payload Format:**
```
[Opcode: 0x0A] [Entity ID 1 (4 bytes)] [Entity ID 2 (4 bytes)]
```


**Parameters:**
- `entityOneId` (uint32_t) - ID of the first entity
- `entityTwoId` (uint32_t) - ID of the second entity

**Usage:**
```c++
packet.collision(bulletId, enemyId);
```


---

### 0x0B - Entity Death

**Purpose:** Notify that an entity has been destroyed

**Payload Format:**
```
[Opcode: 0x0B] [Entity ID (4 bytes)]
```


**Parameters:**
- `id` (uint32_t) - ID of the dead entity

**Usage:**
```c++
packet.dead(enemyId);
```


---

### 0x0C - End Game Status

**Purpose:** Signal game end with winner/loser status

**Payload Format:**
```
[Opcode: 0x0C] [Status (1 byte)]
```


**Parameters:**
- `status` (uint8_t) - 0 = game over (lost), 1 = victory (won)

**Usage:**
```c++
packet.endGame(1); // Victory
packet.endGame(0); // Defeat
```


---

### 0x0D - Player Action

**Purpose:** Execute a player action (fire, heal, use power-up, etc.)

**Payload Format:**
```
[Opcode: 0x0D] [Entity ID (4 bytes)] [Action ID (1 byte)] [Data (4 bytes)]
```


**Parameters:**
- `id` (uint32_t) - ID of the entity performing the action
- `action` (uint8_t) - Action type identifier
- `data` (uint32_t) - Action-specific data (value depends on action type)

**Action Types:**
- `0` - FIRE (shoot)
- `1` - HEAL (restore health)
- `2` - BEAM (special attack)
- `3` - SHIELD (defense ability)
- `4` - MANA (mana restoration, data = new mana value)

**Usage:**
```c++
packet.action(playerId, FIRE, 0);        // Fire weapon
packet.action(playerId, MANA, 50);       // Set mana to 50
packet.action(playerId, HEAL, 25);       // Heal 25 HP
```


---

### 0x0E - Player Ready Status

**Purpose:** Signal that a player is ready to start the game

**Payload Format:**
```
[Opcode: 0x0E] [Player ID (4 bytes)]
```


**Parameters:**
- `playerId` (uint32_t) - ID of the ready player

**Usage:**
```c++
packet.ready(playerId);
```


---

### 0x0F - Start Game Signal

**Purpose:** Signal the server to start the game for all connected players

**Payload Format:**
```
[Opcode: 0x0F]
```


**Usage:**
```c++
packet.startGame();
```


---

## Packet Lifecycle

### Client → Server Flow

1. **Build Packet**: Construct the packet with required header fields
2. **Add Payload**: Use opcode methods to add commands to the payload
3. **Send**: Transmit the packet to the server via UDP
4. **Server Processing**: Server receives and parses the packet

### Server → Client Flow

1. **Build Response**: Create a packet with appropriate opcodes
2. **Send Response**: Transmit to the client via UDP
3. **Client Parsing**: Client receives and interprets the packet
4. **Update Game State**: Apply changes to game entities and components

---

## Packet Parsing (Server-Side)

The `Packetreader` class handles incoming packets from clients:

1. **Header Extraction**: Reads the 12-byte UDP header
2. **Payload Separation**: Extracts the payload data
3. **Opcode Interpretation**: Processes commands based on opcode
4. **Action Dispatch**: Calls appropriate game logic methods

### Example Parsing Flow

```
Receive raw UDP data
    ↓
Extract 12-byte header (ID, ACK, PacketNbr, etc.)
    ↓
Extract variable-length payload
    ↓
Read first opcode byte
    ↓
Switch on opcode and read command-specific data
    ↓
Call appropriate game handler (e.g., updatePosition, handleCollision)
    ↓
Continue until end of packet
```


---

## Error Handling

### Validation Rules

- All required header fields must be set before sending
- Packet payload cannot exceed 116 bytes
- Invalid opcodes are logged and skipped
- Malformed data (incomplete reads) terminates parsing

### Common Errors

| Error | Cause | Handling |
|-------|-------|----------|
| Missing packet parameter | Header field not set | Throws `MissingPacketParameterError` |
| Packet too small | Received data < 12 bytes | Logged, packet ignored |
| Unknown opcode | Invalid opcode value | Logged, parsing stops |
| Incomplete payload | Data cut off mid-command | Parsed fields are used, rest ignored |

---

## Performance Considerations

### Optimization Strategies

1. **Batching**: Combine multiple commands in a single packet when possible
2. **Size Limits**: Keep payloads under 116 bytes to fit in single UDP packet
3. **Selective Updates**: Only send position updates when movement occurs
4. **Header Reuse**: The same header can be used for multiple payload types

### Network Efficiency

- **Single Packet Delivery**: Most game updates fit within UDP MTU (~1500 bytes)
- **No Fragmentation**: 128-byte max packet size prevents IP fragmentation
- **Unreliable Delivery**: UDP trade-off for low latency
- **Acknowledgment System**: ACK field allows retransmission if needed

---

## Integration Example

### Sending Player Movement

```c++
// In Game::playerInput()
if (moved) {
    _packet.updatePosition(entityId, newX, newY);
    _packet.setAck(1);
    _packet.setId(playerId);
    _packet.setPacketNbr(1);
    _packet.setTotalPacketNbr(1);
    _network.sendPacket(_packet);
    _packet.clear();
}
```


### Receiving and Processing

```c++
// In Packetreader::interpretPacket()
case 0x09: {
    uint32_t id;
    uint16_t type;
    float x, y;
    if (payload >> id >> type >> x >> y) {
        if (type == 0) {
            // Update existing entity position
            _game->serverUpdatePosition(id, x, y);
        } else {
            // Spawn new entity
            _game->handleNewPlayer();
        }
    }
    break;
}
```


---

## Best Practices

1. **Always Set Header Fields**: Ensure all header fields are initialized before sending
2. **Clear Between Packets**: Call `clear()` after sending to reset payload
3. **Batch Operations**: Group related commands in a single packet
4. **Validate Data**: Check entity existence before processing position updates
5. **Log Packet Flow**: Use console output during development to track packet flow
6. **Handle Stale Data**: Ignore outdated position updates from network latency
7. **Test with Latency**: Simulate network delays during development

---

## Future Extensions

Potential enhancements to the packet system:

- **Compression**: Compress payload data for slower connections
- **Fragmentation**: Support packets larger than 128 bytes
- **Reliability Layer**: Implement guaranteed delivery for critical commands
- **Encryption**: Add encryption for security
- **Custom Opcodes**: Allow game-specific opcode definitions
- **Bandwidth Monitoring**: Track and optimize packet sizes

