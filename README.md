# ⚔️ Lockstep RTS Prototype

<<<<<<< HEAD
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
=======
A lightweight, scalable real-time strategy (RTS) prototype built in C++ with SFML.  
Designed for single-player with future support for AI opponents and lockstep multiplayer.
>>>>>>> f9e29ef (modified readme and added docs/projectblueprint)

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



---

<<<<<<< HEAD
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
>>>>>>> f9e29ef (modified readme and added docs/projectblueprint)

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

