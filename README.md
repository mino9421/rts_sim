# ⚔️ Lockstep RTS Prototype

## 1. Vision & Goals

> "A 2D RTS game with economic and combat systems, supporting single & future multiplayer."

**Key MVP Features:**
- Unit creation & selection
- Builder system for buildings
- Resource income via Depot
- Combat system (basic damage + health)
- HUD with hotkeys and credit display
- Team-based entity coloring

**Future Features (Post-MVP):**
- Group select box
- AI enemy logic
- Multiplayer system
- Save/load system
- Lobby system with color/faction/team picker

A lightweight, scalable real-time strategy (RTS) prototype built in C++ with SFML.  
Designed for single-player with future support for AI opponents and lockstep multiplayer.

---

## 🧠 Project Vision

**Core Goal:**  
Build a playable RTS framework with essential economic and combat mechanics — extensible into a full-featured multiplayer experience.

**Current Focus:**
- Clear architecture with separated systems
- Fast iteration via MVP-driven development
- Debug-friendly sandbox environment

---

## 🚀 MVP Features

- ✅ Single-unit selection (click)
- ✅ Building via builder unit (Barracks, Depot)
- ✅ Resource generation system (Depot)
- ✅ Soldier production system (Barracks)
- ✅ Basic team coloring (player vs enemy)
- ✅ Click-to-move mechanics
- ✅ HUD displaying credits + hotkey hints
- ✅ Debug toggle to control enemy units (`]` key)

---

## 🔮 Future Roadmap

**Post-MVP Features:**
- [ ] Group drag-select logic
- [ ] Health and damage system
- [ ] Enemy AI logic
- [ ] Multiplayer via lockstep engine
- [ ] Lobby system (team/color/faction picker)
- [ ] Save/load system
- [ ] Pre-game main menu

---

## 🧱 Architecture Overview

| Component        | Description                             |
|------------------|-----------------------------------------|
| `GameSystem`     | Logic for movement, building, production |
| `RenderSystem`   | Draws grid, units, HUD, overlays         |
| `SelectionSystem`| Handles click and drag selection         |
| `GameUtils`      | Helpers like findFreeTile(), isOccupied |
| `GameState`      | Centralized state model (entities, credits, etc.) |

---

## 🛠️ Controls

| Action                     | Key         |
|----------------------------|-------------|
| Select unit/building       | Left Click  |
| Deselect all               | Escape      |
| Move unit                  | Right Click |
| Build Barracks             | B (with Builder selected) |
| Build Depot                | H (with Builder selected) |
| Train Soldier (Barracks)   | S           |
| Train Builder (Cmd Center) | B           |
| Toggle enemy control       | `]` key     |

---

## 📁 Folder Structure

# Project Blueprint & Execution Framework

## 1. Vision & Goals

**One-liner Goal:**  
> "A 2D RTS game with economic and combat systems, supporting single & future multiplayer."

**Key MVP Features:**
- Unit creation & selection
- Builder system for buildings
- Resource income via Depot
- Combat system (basic damage + health)
- HUD with hotkeys and credit display
- Team-based entity coloring

**Future Features (Post-MVP):**
- Group select box
- AI enemy logic
- Multiplayer system
- Save/load system
- Lobby system with color/faction/team picker

---

## 2. Entity & GameState Design

### **Entity Design:**
```cpp
struct Entity {
    std::string type;      // e.g., "Soldier", "Barracks"
    int x, y;
    int team = 1;
    int health = 100;
    bool selected = false;
    // Movement
    int targetX = -1, targetY = -1;
    // Building system
    bool isBuilding = false;
    std::string buildQueued;
    int buildOnX = -1, buildOnY = -1;
    float buildTimer = 0.0f;
    // Production/Harvest
    std::queue<std::string> productionQueue;
    float productionTimer = 0.0f;
    float harvestTimer = 0.0f;
};
```

### **GameState:**
```cpp
struct GameState {
    std::vector<Entity> entities;
    std::vector<Entity> buildings;
    int credits = 10000;
    bool buildMode = false;
    std::string buildTypeQueued;
    bool debugControlEnemies = false;
};
```

---

## 3. System Architecture

**Core Systems:**
- `GameSystem`: Update logic for movement, production
- `RenderSystem`: Draw entities, HUD, overlays
- `SelectionSystem`: Drag box & single click
- `GameUtils`: Utility helpers (findFreeTile, etc.)

**Future Systems:**
- `CombatSystem`
- `AIController`
- `NetworkSystem`
- `LobbySystem`

---

## 4. Execution Methodology

**Milestone Cycle Template (2–3 days)**
```
Goal: Add basic soldier damage system

1. Add health to Entity
2. Add attack range/timer
3. Loop: if enemy in range -> reduce health
4. Remove units with <= 0 health
5. Display health bar
6. Add HUD tooltip when selected
```

> Freeze scope until all steps complete. Only after that, refactor or polish.

---

## 5. Multiplayer Ready Design (Plan Ahead)

- Design entity/team logic with `teamId`
- Input = commands (MoveUnit, Build)
- Store `GameState` in clean object for serialization
- Desync protection via Lockstep (future)

---

## 6. Debugging & Dev Tools

**Toggle Keys:**
- `]` key = toggle control over enemy units (for debug)

**Suggested Add-ons:**
- `DebugOverlay`: Show FPS, selection info, queued actions
- `Toggle AI`: Enable/disable simple AI for testing

---

## 7. UX / QoL

- Use lowercase for units, UPPERCASE for buildings
- Show HUD at bottom (key hints)
- Highlight selected units
- Add proper box drawing for drag select
- Deselect with `Escape`
- Build cancel logic

---

## 8. Refactor / Cleanup Cycle

Every 3-4 added features:
- Rename ambiguous vars (e.g., `b` to `building`)
- Move constants into `GameConfig.h`
- Separate draw vs logic vs input cleanly

---

## 9. Future GitHub/Project Folder Layout

```
/lockstep-rts/
├── assets/
│   └── arial.ttf
├── include/
│   ├── Entity.h
│   ├── GameState.h
│   ├── GameSystem.h
│   ├── RenderSystem.h
│   └── GameUtils.h
├── src/
│   ├── GameSystem.cpp
│   ├── RenderSystem.cpp
│   └── ...
├── main.cpp
└── README.md
```


---


## 10. Notes From Architect

- Done well with logic-first planning.
- Clean system names and separation.
- Don’t over-plan AI or Multiplayer too early.
- Track all future ideas in a markdown TODO file.
- Don’t forget fun: tweak feedback loops, sounds, etc.
=======
## 🧪 Debug Features

- Press `]` to toggle player control over enemy units
- Future plan: `DebugOverlay` (FPS, queued actions, AI state, etc.)

---

## 🎨 UI/UX Details

- Units are labeled in **lowercase** (e.g., `s` = soldier, `b` = builder)
- Buildings use **UPPERCASE** (e.g., `B` = Barracks, `C` = Command Center)
- Green = player, Red = enemy
- Selection highlight + HUD tooltips

---

## 📜 License

MIT – see [`LICENSE`](./LICENSE)

---

> Designed with modularity, clarity, and future-proofing in mind.
> Contributions and feedback welcome!

