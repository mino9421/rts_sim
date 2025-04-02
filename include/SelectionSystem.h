// SelectionSystem.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"

namespace SelectionSystem {
    void selectUnitsInBox(const sf::Vector2f& start, const sf::Vector2f& end, std::vector<Entity>& entities);
    void drawSelectionBox(sf::RenderWindow& window, bool isSelecting, const sf::Vector2f& start, const sf::Vector2f& current);
}
