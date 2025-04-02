#pragma once
#include <SFML/Graphics/Color.hpp>

// Tile & Map configuration
constexpr int TILE_SIZE = 32;
constexpr int MAP_WIDTH = 20;
constexpr int MAP_HEIGHT = 15;

// Starting credits
constexpr int INITIAL_CREDITS = 10000;

// Build times (in seconds)
constexpr float BUILDER_BUILD_TIME = 3.0f;
constexpr float SOLDIER_PRODUCTION_TIME = 1.5f;
constexpr float BUILDER_PRODUCTION_TIME = 3.0f;

// Depot economy
constexpr float DEPOT_GENERATION_INTERVAL = 15.0f;
constexpr int DEPOT_GENERATION_AMOUNT = 2500;

// Unit/building costs
inline int getCost(const std::string& type) {
    if (type == "Soldier") return 200;
    if (type == "Builder") return 1000;
    if (type == "Barracks") return 800;
    if (type == "Depot") return 2000;
    return 0;
}

inline const sf::Color builderColor = sf::Color::Green;
inline const sf::Color soldierColor = sf::Color::White;
inline const sf::Color barracksColor = sf::Color(180, 0, 0);
inline const sf::Color depotColor = sf::Color(255, 140, 0);
inline const sf::Color ccColor = sf::Color::Blue;
inline const sf::Color selectedOutline = sf::Color::Yellow;
