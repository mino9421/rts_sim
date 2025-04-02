#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameState.h"

namespace GameSystem {
    void updateEntities(float dt, GameState& state);
    void updateBuildings(float dt, GameState& state);

    void handleKeyInput(const sf::Event& event, GameState& state);
    void handleMouseInput(const sf::Event& event, GameState& state);
}

