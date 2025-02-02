```mermaid
sequenceDiagram
    participant c as Client
    participant r as Room

    r->>r: BroadcastWinner()
    loop Players
        r->>c: NotifyWinner(Nickname)
    end
```
