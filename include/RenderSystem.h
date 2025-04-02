#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "GameState.h"


namespace RenderSystem {
    void drawGrid(sf::RenderWindow& window);
    void drawEntities(sf::RenderWindow& window, const std::vector<Entity>& entities);
    void drawBuildings(sf::RenderWindow& window, const std::vector<Entity>& buildings);
    void drawHUD(sf::RenderWindow& window, const GameState& state);
}

