#include "GameSystem.h"
#include "GameUtils.h"
#include <iostream>

namespace GameSystem {

void updateEntities(float dt, GameState& state) {
    for (auto& e : state.entities) {
        if (e.targetX != -1 && e.targetY != -1) {
            if (e.x < e.targetX) ++e.x;
            else if (e.x > e.targetX) --e.x;

            if (e.y < e.targetY) ++e.y;
            else if (e.y > e.targetY) --e.y;

            if (e.x == e.targetX && e.y == e.targetY) {
                e.targetX = e.targetY = -1;
                if (!e.buildQueued.empty()) {
                    e.isBuilding = true;
                    e.buildTimer = 3.0f;
                    std::cout << "[Build] Construction started...\n";
                }
            }
        } else if (e.isBuilding) {
            e.buildTimer -= dt;
            if (e.buildTimer <= 0.0f) {
                state.buildings.push_back({e.buildQueued, e.buildOnX, e.buildOnY});
                std::cout << "[Build] " << e.buildQueued << " completed at (" << e.buildOnX << ", " << e.buildOnY << ")\n";
                e.isBuilding = false;
                e.buildQueued = "";
                e.buildOnX = e.buildOnY = -1;
            }
        }
    }
}

void updateBuildings(float dt, GameState& state) {
    for (auto& b : state.buildings) {
        if (b.type == "Depot") {
            b.harvestTimer += dt;
            if (b.harvestTimer >= 15.0f) {
                state.credits += 2500;
                b.harvestTimer = 0.0f;
                std::cout << "[Economy] Depot generated 2500 credits. Total: " << state.credits << "\n";
            }
        }

        if (!b.productionQueue.empty()) {
            if (b.productionTimer <= 0.0f) {
                auto spot = findAdjacentFree(b.x, b.y, state.entities, state.buildings);
                if (spot) {
                    std::string type = b.productionQueue.front();
                    b.productionQueue.pop();
                    state.entities.push_back({type, spot->first, spot->second});
                    std::cout << "[Production] " << type << " created at (" << spot->first << ", " << spot->second << ")\n";
                    b.productionTimer = (type == "Builder" ? 3.0f : 1.5f);
                }
            } else {
                b.productionTimer -= dt;
            }
        }
    }
}

void handleKeyInput(const sf::Event& event, GameState& state) {
    if (event.type != sf::Event::KeyPressed) return;

    // --- [S] → Produce Soldier from Barracks ---
    if (event.key.code == sf::Keyboard::S) {
        for (auto& b : state.buildings) {
            if (b.selected && b.type == "Barracks") {
                int cost = getCost("Soldier");
                if (state.credits >= cost) {
                    b.productionQueue.push("Soldier");
                    state.credits -= cost;
                    std::cout << "[Production] Soldier queued (200 credits). Remaining: " << state.credits << "\n";
                } else {
                    std::cout << "[Credits] Not enough to produce Soldier.\n";
                }
            }
        }
    }

    // --- [B or H] → Builder triggers build mode for Barracks/Depot ---
    if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::H) {
        bool builderSelected = false;
        for (const auto& e : state.entities) {
            if (e.selected && e.type == "Builder") {
                builderSelected = true;
                break;
            }
        }

        if (builderSelected) {
            state.buildTypeQueued = (event.key.code == sf::Keyboard::B) ? "Barracks" : "Depot";
            int cost = getCost(state.buildTypeQueued);
            if (state.credits >= cost) {
                state.buildMode = true;
                std::cout << "[Input] Build mode activated for: " << state.buildTypeQueued << "\n";
            } else {
                std::cout << "[Credits] Not enough to build " << state.buildTypeQueued << "\n";
            }
            return; // prevents also queuing Builder from CommandCenter
        }
    }

    // --- [B] → Command Center produces Builder (only if selected) ---
    if (event.key.code == sf::Keyboard::B) {
        for (auto& b : state.buildings) {
            if (b.selected && b.type == "CommandCenter") {
                int cost = getCost("Builder");
                if (state.credits >= cost) {
                    b.productionQueue.push("Builder");
                    state.credits -= cost;
                    std::cout << "[Production] Builder queued (1000 credits). Remaining: " << state.credits << "\n";
                } else {
                    std::cout << "[Credits] Not enough to produce Builder.\n";
                }
            }
        }
    }
}


void handleMouseInput(const sf::Event& event, GameState& state) {
    if (event.type == sf::Event::MouseButtonPressed) {
        int gridX = event.mouseButton.x / 32;
        int gridY = event.mouseButton.y / 32;

        if (event.mouseButton.button == sf::Mouse::Left && state.buildMode) {
            if (isOccupiedByAny(gridX, gridY, state.entities, state.buildings)) {
                std::cout << "[Build] Cannot build on occupied tile.\n";
                state.buildMode = false;
                return;
            }

            for (auto& e : state.entities) {
                if (e.selected && e.type == "Builder") {
                    auto spot = findAdjacentFree(gridX, gridY, state.entities, state.buildings);
                    if (spot) {
                        int cost = getCost(state.buildTypeQueued);
                        state.credits -= cost;
                        std::cout << "[Build] Spent " << cost << ", remaining: " << state.credits << "\n";
                        e.targetX = spot->first;
                        e.targetY = spot->second;
                        e.buildOnX = gridX;
                        e.buildOnY = gridY;
                        e.buildQueued = state.buildTypeQueued;
                    } else {
                        std::cout << "[Build] No free tile near build site.\n";
                    }
                    break;
                }
            }
            state.buildMode = false;
        }

        if (event.mouseButton.button == sf::Mouse::Left && !state.buildMode) {
            for (auto& e : state.entities) e.selected = false;
            for (auto& e : state.entities) {
                if (e.x == gridX && e.y == gridY) e.selected = true;
            }
            for (auto& b : state.buildings) b.selected = false;
            for (auto& b : state.buildings) {
                if (b.x == gridX && b.y == gridY) b.selected = true;
            }
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            for (auto& e : state.entities) {
                if (e.selected && !e.isBuilding) {
                    e.targetX = gridX;
                    e.targetY = gridY;
                }
            }
        }
    }
}

} // namespace GameSystem

