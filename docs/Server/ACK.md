
# ACK (Acknowledgment) System Documentation

## Overview

The R-Type ACK system is a reliability mechanism for critical game packets sent over UDP. Since UDP is connectionless and unreliable, the ACK system ensures that important packets (like entity death notifications) are delivered to all connected clients, even if they are initially lost during transmission.

---

## Architecture

### Core Components

The ACK system consists of three main components:

1. **ACK Storage** - Server maintains a list of unacknowledged packets
2. **ACK Tracking** - Each client tracks which ACKs they need to receive
3. **ACK ID Generator** - Generates unique identifiers for trackable packets

### Data Structures

#### Server-Side ACK Storage
```
cpp
std::vector<std::pair<Packet, u_int32_t>> _ackPackets;
```
- **Packet**: The actual packet data that needs reliable delivery
- **u_int32_t**: The server tick timestamp when the packet was queued
- Stored in both `Server` and `ServerGame` classes

#### Client-Side ACK Tracking
```
cpp
class User {
std::vector<u_int32_t> _ackList;  // List of pending ACK tick IDs
};
```
Each connected user maintains a list of ACK IDs they are waiting to receive.

### ACK ID Generation
```
cpp
static auto getAckId() -> u_int32_t {
static u_int32_t id = 0;
return ++id;
}
```
A simple monotonically increasing counter that generates unique ACK identifiers, incremented with each new trackable packet.

---

## Packet Structure with ACK

### Header Format with ACK Field
```

[ID (4 bytes)] [ACK (4 bytes)] [PacketNbr (1 byte)] [TotalPacketNbr (1 byte)] [DataSize (2 bytes)]
```
The **ACK field (4 bytes)** serves as the acknowledgment identifier when the packet requires guaranteed delivery.

### Usage

When a packet needs reliable delivery:
```
cpp
_packet.setAck(getAckId());      // Set unique ACK ID
_ackPackets.emplace_back(_packet, _tick);  // Store for retransmission
for (auto tmp : _users)
tmp._ackList.emplace_back(_tick);      // Add to each user's pending list
_network.sendPacket(_packet);             // Send to all clients
```
When a packet doesn't need acknowledgment:
```
cpp
_packet.setAck(0);  // Default value means no ACK tracking
```
---

## Workflow

### 1. Sending a Trackable Packet (Server)

**Scenario:** Entity death packet needs guaranteed delivery
```

1. Create packet with death notification
2. Get unique ACK ID using getAckId()
3. Set ACK ID in packet header
4. Store packet with current tick: _ackPackets.push_back({packet, currentTick})
5. Add ACK ID to each connected user's pending list
6. Send packet to all clients via UDP
```
### 2. ACK Timeout and Retransmission (Server Game Loop)

**Executed every frame in `ServerGame::run()`:**
```

Step 1: Clean up old ACKs
├─ Remove ACK packets older than 1500ms (150 ticks at 30fps)
└─ Reason: After 1.5 seconds, assume packet will never be delivered

Step 2: Check client ACK lists
├─ For each user in _users
├─ For each ACK ID in user._ackList
└─ For each packet in _ackPackets

Step 3: Resend if needed
├─ If ACK is older than 500ms (50 ticks)
├─ And still in client's pending list
├─ Resend the packet
└─ Try again next frame if still not acknowledged
```
**Pseudo-code:**
```
cpp
// Cleanup old ACKs (> 1500ms old)
_ackPackets.erase(
std::remove_if(_ackPackets.begin(), _ackPackets.end(),
[this](const std::pair<Packet, u_int32_t>& tmpPacket) {
return tmpPacket.second + 1500 < _tick;
}),
_ackPackets.end()
);

// Retransmit if older than 500ms
for (const auto& user : _users) {
if (_ackPackets.empty()) break;
if (user._ackList.empty()) continue;

    for (auto ackId : user._ackList) {
        for (auto [packet, timestamp] : _ackPackets) {
            if (timestamp == ackId && timestamp + 500 < _tick) {
                _network.sendPacket(packet);  // Resend
            }
        }
    }
}
```
### 3. Client Acknowledgment (Client-Side Network Thread)

**TCP Message Format:**
```

When client receives an ACK packet, it sends TCP acknowledgment:
[ACK Marker] [ACK ID (4 bytes)]
```
### 4. Server Processing ACK Confirmation

**In `Server::tcpThread()`:**

When server receives ACK confirmation from client:

```cpp
uint32_t ackNb = /* extract from TCP message */;

for (auto& user : _users) {
    if (std::find(user._ackList.begin(), user._ackList.end(), ackNb) 
        != user._ackList.end()) {
        
        // Remove ACK from user's pending list
        user._ackList.erase(
            std::remove(user._ackList.begin(), user._ackList.end(), ackNb),
            user._ackList.end()
        );
        break;
    }
}
```
```


---

## Timing Parameters

| Parameter | Value | Purpose |
|-----------|-------|---------|
| **Retransmit Timeout** | 500ms (50 ticks) | Wait before resending if not acked |
| **Max Packet Age** | 1500ms (150 ticks) | Maximum time to keep packet in storage |
| **Game Tick Rate** | 30 FPS | 33.33ms per tick |
| **Effective Window** | 1500ms | Time window for ACK delivery attempts |

---

## Packet Types Using ACK System

### Death Notification (0x0B)

Most critical packet for ACK tracking:

```c++
hp->setAlive(false);
_packet.dead(entity->getId());                    // Opcode 0x0B
_packet.setAck(getAckId());                       // Enable ACK tracking
_ackPackets.emplace_back(_packet, _tick);         // Store for retry
for (auto tmp : _users)
    tmp._ackList.emplace_back(_tick);             // Add to all users
_network.sendPacket(_packet);                     // Send to clients
```


### Other Packets

Most other game packets use `setAck(0)` as they are frequently updated:

```c++
_packet.updatePosition(id, x, y);
_packet.setAck(0);           // No ACK needed - updated next frame anyway
_network.sendPacket(_packet);
```


---

## State Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│ Server Creates Critical Packet (e.g., Entity Death)             │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────────────┐
│ Assign Unique ACK ID via getAckId()                             │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────────────┐
│ Store Packet in _ackPackets with Current Tick                   │
│ Add ACK ID to Each User's _ackList                              │
└──────────────────────┬──────────────────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────────────────┐
│ Send via UDP to All Connected Clients                           │
└──────────────────────┬──────────────────────────────────────────┘
                       │
        ┌──────────────┴──────────────┐
        │                             │
        ▼                             ▼
   ┌─────────────┐          ┌────────────────┐
   │ Delivered   │          │ Lost (UDP)     │
   └──────┬──────┘          └────────┬───────┘
          │                          │
          ▼                          ▼
    ┌──────────────┐      ┌──────────────────┐
    │ Client ACK   │      │ Resend at 500ms  │
    │ via TCP      │      │ (if ack + 500ms  │
    └──────┬───────┘      │  < current tick) │
           │              └──────────┬───────┘
           ▼                         │
    ┌─────────────────┐      ┌──────────────┐
    │ Server removes  │      │ Retry every  │
    │ ACK from user's │      │ 500ms up to  │
    │ _ackList        │      │ 1500ms total │
    └─────────────────┘      └──────┬───────┘
                                    ▼
                           ┌──────────────────┐
                           │ Cleanup if older │
                           │ than 1500ms      │
                           └──────────────────┘
```


---

## Benefits

### 1. Guaranteed Delivery
- Critical packets (deaths, game state changes) are guaranteed to reach clients
- Automatic retransmission handles packet loss

### 2. Low Latency
- Uses UDP for fast initial delivery
- Only resends if needed
- No connection overhead like TCP

### 3. Transparent to Game Logic
- Game code doesn't need to handle retransmissions
- ACK system manages all retry logic

### 4. Scalable
- Each user tracks their own pending ACKs independently
- Server can handle many clients efficiently
- Cleanup mechanism prevents unbounded memory growth

---

## Implementation Details

### Memory Management

**ACK Packet Storage:**
- Packets stored up to 1500ms old (150 frames at 30fps)
- Old packets automatically removed to prevent memory leaks
- Estimated max storage: 10-20 packets depending on game state frequency

**User ACK List:**
- Each user has own list of pending ACK IDs
- Automatically cleaned when server receives TCP ACK
- Independent per-user tracking prevents queue blocking

### Thread Safety

**Components:**
- `_ackPackets` accessed in game loop and ACK processing
- `_ackList` accessed in network threads (TCP) and game loop
- No explicit locks used (single-threaded game loop with synchronized network threads)

**Potential Issues:**
- Race condition if TCP thread modifies `_ackList` while game loop reads it
- Should add thread synchronization if increasing network throughput

---

## Debugging and Monitoring

### Logging Points

1. **Packet Queued**: When packet added to `_ackPackets`
2. **Packet Sent**: Initial transmission
3. **Packet Resent**: Retry after 500ms timeout
4. **Packet Removed**: When ACK received from all clients
5. **Cleanup**: When packets older than 1500ms removed

### Common Issues

| Problem | Cause | Solution |
|---------|-------|----------|
| Packet never acknowledged | Client disconnected | Remove user's ACK list entries |
| Memory growth | Old packets not cleaned | Check timeout values (1500ms) |
| Too many retransmits | Network packet loss | Increase retry timeout window |
| Duplicate packets | Retransmission race | Ensure server/client sync |

---

## Best Practices

1. **Use ACK for Critical Events**: Death, game end, level start
2. **Don't Use ACK for Updates**: Position, animation updates (sent frequently)
3. **Monitor ACK Lists**: Check for stuck packets that won't transmit
4. **Test with Loss**: Simulate 10-20% packet loss to validate ACK behavior
5. **Set Appropriate Timeouts**: Balance between retry attempts and latency
6. **Log ACK Activity**: Track ACK success rate for network diagnostics

---

## Future Improvements

1. **Adaptive Timeout**: Dynamically adjust retry timeout based on network latency
2. **Per-Client Prioritization**: Prioritize critical ACKs for clients with packet loss
3. **ACK Compression**: Batch multiple ACKs into single packet
4. **Bandwidth Monitoring**: Track ACK overhead and optimize
5. **Client-Side ACK Optimization**: Allow clients to batch multiple acknowledgments
6. **Network Statistics**: Collect and report ACK success/failure rates
```
