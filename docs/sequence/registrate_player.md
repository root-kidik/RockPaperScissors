```mermaid
sequenceDiagram
    participant c as Client
    participant s as Server

    c->>s: Registrate(Nickname)
    alt Nickname unique on Server:
        r->>c: PlayerID
    else
        r->>c: Error
    end
```
