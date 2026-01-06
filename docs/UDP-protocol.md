# UDP Protocol Documentation

## 1. Overview

This document describes a custom **UDP-based protocol** designed for fast, real-time communication between a client and a server (e.g. multiplayer game networking).

The protocol prioritizes low latency and optionally supports basic reliability and fragmentation mechanisms at the application level.

---

## 2. General Information

| Item | Value |
|------|-------|
| Transport | UDP |
| Packet Size | **128 bytes (fixed)** |
| Header Size | **12 bytes** |
| Max Payload Size | **116 bytes** |


---

## 3. Packet Layout

Each UDP datagram follows this structure:


- The **Command** field identifies the message type.
- The **Payload** format depends on the command.
- The `DataSize` field in the header specifies the actual payload size.

---

## 4. UDP Header Structure (12 bytes)

| Field | Size (bytes) | Type | Description |
|------|-------------|------|-------------|
| ID | 4 | uint32 | Unique entity or player identifier |
| ACK | 4 | uint32 | Last acknowledged packet number |
| PacketNbr | 1 | uint8 | Index of this packet in a fragmented message |
| TotalPacketNbr | 1 | uint8 | Total number of packets in the message |
| DataSize | 2 | uint16 | Size of payload data in bytes |

### Notes
- If `TotalPacketNbr == 1`, the packet is not fragmented.
- `PacketNbr` starts at **0**.
- `PacketNbr < TotalPacketNbr`.

---

## 5. Reliability Mechanism (Optional)

<-- TODO: Fix ACK and put right information ------------------------------- -->

- The `ACK` field contains the **PacketNbr of the last successfully received packet**.
- Packets not acknowledged within an implementation-defined timeout MAY be retransmitted.
- Reliability is **best-effort** and not guaranteed (UDP semantics apply).

---

## 6. Fragmentation Rules

If a message payload exceeds the maximum payload size:

- The message is split into multiple packets.
- All fragments share the same `ID`.
- Fragments are reassembled using:
    - `PacketNbr`
    - `TotalPacketNbr`
- A message MUST NOT be processed until **all fragments are received**.

---

## 7. Client → Server

### 7.1 Position Update
| Command Name | Code |
|-------------|------|
| SendPosition | `0x07` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| ID | uint32 | 4 |
| x | float32 | 4 |
| y | float32 | 4 |


**Description:**  
The client sends its current position to the server.

---

### 7.2 Action
| Command Name | Code |
|-------------|------|
| Action | `0x0B` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| ID | uint32 | 4 |
| ActionId | uint8 | 1 |


**Description:**  
The client sends an action performed by an entity.

---

## 8. Server → Client

### 8.1 Time Synchronization
| Command Name | Code |
|-------------|------|
| TimeSync | `0x06` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| Time | uint32 | 4 |

**Description:**  
The server sends the current server timestamp (milliseconds since epoch).

---

### 8.2 Entity Spawn / Position Update
| Command Name | Code |
|-------------|------|
| EntityUpdate | `0x07` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| ID | uint32 | 4 |
| Type | uint16 | 2 |
| x | float32 | 4 |
| y | float32 | 4 |

**Description:**  
- **When `Type != 0`:** The server sends a **new entity** to the client.
- **When `Type == 0`:** The server sends the **current position** of the entity.

---

### 8.3 Collision
| Command Name | Code |
|-------------|------|
| Collision | `0x08` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| EntityID1 | uint32 | 4 |
| EntityID2 | uint32 | 4 |

**Description:**  
Indicates that two entities have collided.

---

### 8.4 Entity Death
| Command Name | Code |
|-------------|------|
| Dead | `0x09` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| ID | uint32 | 4 |


**Description:**  
Notifies the client that an entity has died.

---

### 8.5 Game End
| Command Name | Code |
|-------------|------|
| EndGame | `0x0A` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| Result | uint8 | 1 |

**Result values:**
- `0` = Lose
- `1` = Win

---

### 8.6 Action (Server Broadcast)
| Command Name | Code |
|-------------|------|
| Action | `0x0B` |

| Field | Type | Size |
|-----|-----|-----|
| Command | uint8 | 1 |
| ID | uint32 | 4 |
| ActionId | uint8 | 1 |

**Description:**  
Broadcasts an action performed by an entity to clients.

---

## 9. Command Code Scope

- Command codes are **direction-dependent**.
- The same command value MAY be used for both client→server and server→client messages.

---

## 10. Notes

- UDP is used to minimize latency.
- Packet loss is tolerated.
- Application-level reliability is optional and lightweight.
- This protocol does not provide encryption or authentication.
