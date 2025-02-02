```mermaid
sequenceDiagram
    participant c as Client
    participant r as Room

    r->>r: BroadcastPlayTable()
    loop Players
        r->>c: NotifyPlayTable()
    end
```
