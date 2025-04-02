#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "GameState.h"


namespace RenderSystem {
    void drawGrid(sf::RenderWindow& window);
    void drawEntities(sf::RenderWindow& window, const std::vector<Entity>& entities, const sf::Font& font);
    void drawBuildings(sf::RenderWindow& window, const std::vector<Entity>& buildings, const sf::Font& font);    
    void drawHUD(sf::RenderWindow& window, const GameState& state);
}

