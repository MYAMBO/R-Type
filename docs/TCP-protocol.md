# TCP Protocol Documentation

## Purpose
TCP is used for reliable communication of authentication, session management, and game state initialization.

---

## Client → Server Messages

| Command         | Code   | Fields            | Description                   |
|-----------------|--------|-------------------|-------------------------------|
| Connect Request | `0x01` | -                 | Requests connection to server |
| Login           | `0x02` | `Name (15 bytes)` | Sends player username         |
| Ready           | `0x03` | `ReadyStatus (1)` | `0 = not ready`, `1 = ready`  |
| Select Level    | `0x06` | `Level Id`        | Send selected level           |
| Upload level    | `0x07` | `Level file`      | Send a new map to the server  |

---

## Server → Client Messages

| Command              | Code | Fields                         | Description                     |
|----------------------|------|--------------------------------|---------------------------------|
| Connect Response     | `0x01` | `PlayerID (1)` - `UDPPort (4)` | Assigns player ID and UDP port  |
| Login Response       | `0x02` | `Status (1)`                   | `0 = fail`, `1 = success`       |
| Ready Acknowledgment | `0x03` | -                              | Confirms all players are ready  |
| Game Start           | `0x04` | -                              | Game officially starts          |
| Game Abort           | `0x05` | -                              | Game aborted or server shutdown |
| Level Selection      | `0x06` | `List of Levels`               | Send list of all Levels         |

---

## Example TCP Communication Flow

```text
Client ----------------> Server
       Connect (0x01)

Client <---------------- Server
  ConnectResp (0x01) PlayerID, UDPPort

Client ----------------> Server
    Login (0x02) Name

Client <---------------- Server
  LoginResp (0x02) Status

Client ----------------> Server
     Ready (0x03)

Client <---------------- Server
   GameStart (0x04)
