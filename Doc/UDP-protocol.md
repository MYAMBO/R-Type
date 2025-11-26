# UDP Protocol Documentation

## General Information
| Item | Value |
|------|-------|
| Packet Size | **128 bytes** |
| Header Size | **12 bytes** |
| Max Data Size | **116 bytes** |

---

## UDP Header Structure

| Field | Size (bytes) | Description |
|-------|--------------|-------------|
| ID | 4 | Unique entity or player identifier |
| ACK | 4 | Acknowledgment number (reliability mechanism) |
| PacketNbr | 1 | Current packet number (for fragmented packets) |
| TotalPacketNbr | 1 | Total number of packets in sequence |
| DataSize | 2 | Payload size in bytes |

---

## Client → Server Messages

| Command | Code | Fields | Description |
|---------|------|--------|-------------|
| Time Sync Request | `0x06` | - | Client requests current server time |

---

## Server → Client Messages

### Time Response
| Command | Code | Fields | Description |
|---------|------|--------|-------------|
| Time Response | `0x06` | `Time (4 bytes)` | Server sends current timestamp |

---

### Entity/Position Update
| Command | Code | Fields | Description |
|---------|------|--------|-------------|
| Send Position/Spawn | `0x07` | `ID (4)` - `Type (2)` - `x (4)` - `y (4)` | Spawns or updates entity/player position |

---

### Hit Notification
| Command | Code | Fields | Description |
|---------|------|--------|-------------|
| Hit | `0x08` | `ID (4)` - `Value (4)` | Indicates an entity has taken damage or scored |

---

### Entity Death
| Command | Code | Fields | Description |
|---------|------|--------|-------------|
| Dead | `0x09` | `ID (4)` | Entity is dead |

---

### Game End
| Command | Code | Fields | Description |
|---------|------|--------|-------------|
| EndGame | `0x0A` | `Result (1)` | `0 = lose`, `1 = win` |

---

## Notes
- UDP is used for fast, real-time updates.
- ACK can be used to add reliability if needed.
- Fragmentation fields allow large messages to be split.
