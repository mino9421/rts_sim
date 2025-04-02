// main.cpp - Command Center produces Builders, and is now a building
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include <queue>

struct Entity {
    std::string type;
    int x, y;
    int targetX = -1, targetY = -1;
    bool selected = false;
    bool isBuilding = false;
    float buildTimer = 0.0f;
    int buildOnX = -1, buildOnY = -1;
    std::string buildQueued;
    std::queue<std::string> productionQueue;
    float productionTimer = 0.0f;
    float harvestTimer = 0.0f;
};

const int TILE_SIZE = 32;
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 15;

int playerCredits = 10000;

int getCost(const std::string& type) {
    if (type == "Soldier") return 200;
    if (type == "Builder") return 1000;
    if (type == "Barracks") return 800;
    if (type == "Depot") return 2000;
    return 0;
}

bool isOccupied(int x, int y, const std::vector<Entity>& all) {
    for (const auto& e : all) {
        if (e.x == x && e.y == y)
            return true;
    }
    return false;
}

bool isOccupiedByAny(int x, int y, const std::vector<Entity>& units, const std::vector<Entity>& buildings) {
    return isOccupied(x, y, units) || isOccupied(x, y, buildings);
}

std::optional<std::pair<int, int>> findAdjacentFree(int tx, int ty, const std::vector<Entity>& units, const std::vector<Entity>& buildings) {
    std::vector<std::pair<int, int>> offsets = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };
    for (auto [dx, dy] : offsets) {
        int nx = tx + dx;
        int ny = ty + dy;
        if (nx >= 0 && nx < MAP_WIDTH && ny >= 0 && ny < MAP_HEIGHT && !isOccupiedByAny(nx, ny, units, buildings)) {
            return std::make_pair(nx, ny);
        }
    }
    return std::nullopt;
}

int main() {
    std::cout << "[Startup] Game initialized with 10000 credits.\n";

    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Lockstep RTS Test");
    window.setFramerateLimit(60);

    sf::Clock clock;
    sf::Color ccColor = sf::Color::Blue;
    sf::Color builderColor = sf::Color::Green;
    sf::Color barracksColor = sf::Color(180, 0, 0);
    sf::Color depotColor = sf::Color(255, 140, 0);
    sf::Color soldierColor = sf::Color::White;
    sf::Color selectedOutline = sf::Color::Yellow;

    std::vector<Entity> entities = {
        {"Builder", 6, 5}
    };

    std::vector<Entity> buildings = {
        {"CommandCenter", 5, 5}
    };

    bool buildMode = false;
    std::string buildTypeQueued = "";

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::H) {
                    buildTypeQueued = (event.key.code == sf::Keyboard::B) ? "Barracks" : "Depot";
                    int cost = getCost(buildTypeQueued);
                    if (playerCredits >= cost) {
                        buildMode = true;
                        std::cout << "[Input] Build mode activated for: " << buildTypeQueued << "\n";
                    } else {
                        std::cout << "[Credits] Not enough to build " << buildTypeQueued << "\n";
                    }
                }
                if (event.key.code == sf::Keyboard::S) {
                    for (auto& b : buildings) {
                        if (b.selected && b.type == "Barracks") {
                            int cost = getCost("Soldier");
                            if (playerCredits >= cost) {
                                b.productionQueue.push("Soldier");
                                playerCredits -= cost;
                                std::cout << "[Production] Soldier queued (200 credits). Remaining: " << playerCredits << "\n";
                            } else {
                                std::cout << "[Credits] Not enough to produce Soldier.\n";
                            }
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::B) {
                    for (auto& b : buildings) {
                        if (b.selected && b.type == "CommandCenter") {
                            int cost = getCost("Builder");
                            if (playerCredits >= cost) {
                                b.productionQueue.push("Builder");
                                playerCredits -= cost;
                                std::cout << "[Production] Builder queued (1000 credits). Remaining: " << playerCredits << "\n";
                            } else {
                                std::cout << "[Credits] Not enough to produce Builder.\n";
                            }
                        }
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int gridX = event.mouseButton.x / TILE_SIZE;
                int gridY = event.mouseButton.y / TILE_SIZE;

                if (event.mouseButton.button == sf::Mouse::Left && buildMode) {
                    if (isOccupiedByAny(gridX, gridY, entities, buildings)) {
                        std::cout << "[Build] Cannot build on occupied tile.\n";
                        buildMode = false;
                        continue;
                    }

                    for (auto& e : entities) {
                        if (e.selected && e.type == "Builder") {
                            auto spot = findAdjacentFree(gridX, gridY, entities, buildings);
                            if (spot) {
                                int cost = getCost(buildTypeQueued);
                                playerCredits -= cost;
                                std::cout << "[Build] Spent " << cost << ", remaining: " << playerCredits << "\n";
                                e.targetX = spot->first;
                                e.targetY = spot->second;
                                e.buildOnX = gridX;
                                e.buildOnY = gridY;
                                e.buildQueued = buildTypeQueued;
                            } else {
                                std::cout << "[Build] No free tile near build site.\n";
                            }
                            break;
                        }
                    }
                    buildMode = false;
                }

                if (event.mouseButton.button == sf::Mouse::Left && !buildMode) {
                    for (auto& e : entities) e.selected = false;
                    for (auto& e : entities) {
                        if (e.x == gridX && e.y == gridY) e.selected = true;
                    }
                    for (auto& b : buildings) b.selected = false;
                    for (auto& b : buildings) {
                        if (b.x == gridX && b.y == gridY) b.selected = true;
                    }
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    for (auto& e : entities) {
                        if (e.selected && !e.isBuilding) {
                            e.targetX = gridX;
                            e.targetY = gridY;
                        }
                    }
                }
            }
        }

        for (auto& e : entities) {
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
                    buildings.push_back({e.buildQueued, e.buildOnX, e.buildOnY});
                    std::cout << "[Build] " << e.buildQueued << " completed at (" << e.buildOnX << ", " << e.buildOnY << ")\n";
                    e.isBuilding = false;
                    e.buildQueued = "";
                    e.buildOnX = e.buildOnY = -1;
                }
            }
        }

        for (auto& b : buildings) {
            if (b.type == "Depot") {
                b.harvestTimer += dt;
                if (b.harvestTimer >= 15.0f) {
                    playerCredits += 2500;
                    b.harvestTimer = 0.0f;
                    std::cout << "[Economy] Depot generated 2500 credits. Total: " << playerCredits << "\n";
                }
            }

            if (!b.productionQueue.empty()) {
                if (b.productionTimer <= 0.0f) {
                    auto spot = findAdjacentFree(b.x, b.y, entities, buildings);
                    if (spot) {
                        std::string type = b.productionQueue.front();
                        b.productionQueue.pop();
                        entities.push_back({type, spot->first, spot->second});
                        std::cout << "[Production] " << type << " created at (" << spot->first << ", " << spot->second << ")\n";
                        b.productionTimer = (type == "Builder" ? 3.0f : 1.5f);
                    }
                } else {
                    b.productionTimer -= dt;
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                tile.setFillColor(sf::Color(30, 30, 30));
                window.draw(tile);
            }
        }

        for (auto& e : entities) {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
            shape.setPosition(e.x * TILE_SIZE + 1, e.y * TILE_SIZE + 1);
            if (e.type == "Builder") shape.setFillColor(builderColor);
            else if (e.type == "Soldier") shape.setFillColor(soldierColor);
            if (e.selected) {
                shape.setOutlineColor(selectedOutline);
                shape.setOutlineThickness(2);
            }
            window.draw(shape);
        }

        for (auto& b : buildings) {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
            shape.setPosition(b.x * TILE_SIZE + 1, b.y * TILE_SIZE + 1);
            if (b.type == "Barracks") shape.setFillColor(barracksColor);
            else if (b.type == "Depot") shape.setFillColor(depotColor);
            else if (b.type == "CommandCenter") shape.setFillColor(ccColor);
            if (b.selected) {
                shape.setOutlineColor(selectedOutline);
                shape.setOutlineThickness(2);
            }
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}

