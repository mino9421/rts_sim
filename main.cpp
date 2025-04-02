// main.cpp - Entry point for Lockstep RTS
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameUtils.h"
#include "GameSystem.h"
#include "RenderSystem.h"
#include "GameConfig.h"
#include "GameState.h"

int main() {
    std::cout << "[Startup] Game initialized with 10000 credits.\n";

    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Lockstep RTS Test");
    window.setFramerateLimit(60);

    sf::Clock clock;
    GameState state;
    state.credits = INITIAL_CREDITS;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            GameSystem::handleKeyInput(event, state);
            GameSystem::handleMouseInput(event, state);
        }

        GameSystem::updateEntities(dt, state);
        GameSystem::updateBuildings(dt, state);

        window.clear(sf::Color::Black);
        RenderSystem::drawGrid(window);
        RenderSystem::drawEntities(window, state.entities);
        RenderSystem::drawBuildings(window, state.buildings);
        window.display();
    }

    return 0;
}

