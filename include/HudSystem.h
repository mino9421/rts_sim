// HudSystem.h
#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace HudSystem {
    void drawHUD(sf::RenderWindow& window, const GameState& state);
}
