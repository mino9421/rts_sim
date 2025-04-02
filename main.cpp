// main.cpp - Entry point for Lockstep RTS
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "GameUtils.h"
#include "GameSystem.h"
#include "RenderSystem.h"
#include "GameConfig.h"
#include "GameState.h"
#include "SelectionSystem.h"

int main() {
    std::cout << "[Startup] Game initialized with 10000 credits.\n";

    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Lockstep RTS Test");
    window.setFramerateLimit(60);

    sf::Clock clock;
    GameState state;
    state.credits = INITIAL_CREDITS;

    sf::Vector2i dragStart(-1, -1);
    sf::Vector2i dragEnd(-1, -1);
    bool isDragging = false;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            GameSystem::handleKeyInput(event, state);
            GameSystem::handleMouseInput(event, state);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                dragStart = sf::Mouse::getPosition(window);
                isDragging = true;
            } else if (event.type == sf::Event::MouseMoved && isDragging) {
                dragEnd = sf::Mouse::getPosition(window);
            } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                isDragging = false;
                SelectionSystem::selectUnitsInBox(
                    sf::Vector2f(dragStart.x, dragStart.y),
                    sf::Vector2f(dragEnd.x, dragEnd.y),
                    state.entities
                );
                
                dragStart = dragEnd = {-1, -1};
            }
        }

        GameSystem::updateEntities(dt, state);
        GameSystem::updateBuildings(dt, state);

        window.clear(sf::Color::Black);
        RenderSystem::drawGrid(window);
        RenderSystem::drawEntities(window, state.entities);
        RenderSystem::drawBuildings(window, state.buildings);

        if (isDragging && dragStart.x >= 0 && dragEnd.x >= 0) {
            SelectionSystem::drawSelectionBox(window, isDragging,
                sf::Vector2f(dragStart.x, dragStart.y),
                sf::Vector2f(dragEnd.x, dragEnd.y)
            );
        }

        RenderSystem::drawHUD(window, state);
        window.display();
    }

    return 0;
}