```mermaid
sequenceDiagram
    participant r as Room
    participant c as Client

    r->>r: RandomlySelectPlayerCard()
    r->>c: NotifyPlayerWhatCardForceTurned()
```
