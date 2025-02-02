```mermaid
sequenceDiagram
    participant r as Room

    r->>r: DealMissingCards()
    r->>r: BroadcastDealedMissingCards()
    r->>r: StartTurnTimer()
    r->>r: BroadcastStartedTurnTimer()
```
