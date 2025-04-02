// RenderSystem.cpp - Handles rendering logic
#include "RenderSystem.h"
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "Entity.h"
#include "GameState.h"

namespace RenderSystem {

    void drawHUD(sf::RenderWindow& window, const GameState& state) {
        static sf::Font font;
        static bool loaded = font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    
        if (!loaded) return;
    
        sf::Text creditText("Credits: " + std::to_string(state.credits), font, 16);
        creditText.setPosition(10, 5);
        creditText.setFillColor(sf::Color::White);
    
        sf::Text actionText("", font, 16);
        actionText.setPosition(10, MAP_HEIGHT * TILE_SIZE - 28);
        actionText.setFillColor(sf::Color::Cyan);
    
        for (const auto& e : state.entities) {
            if (e.selected && e.type == "Builder") {
                actionText.setString("Press [B] to build Barracks, [H] for Depot");
            }
        }
    
        for (const auto& b : state.buildings) {
            if (b.selected) {
                if (b.type == "Barracks")
                    actionText.setString("Press [S] to produce Soldier (200)");
                else if (b.type == "CommandCenter")
                    actionText.setString("Press [B] to produce Builder (1000)");
            }
        }
    
        window.draw(creditText);
        window.draw(actionText);
    }

    void drawGrid(sf::RenderWindow& window) {
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
                tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                tile.setFillColor(sf::Color(30, 30, 30));
                window.draw(tile);
            }
        }
    }

    void drawEntities(sf::RenderWindow& window, const std::vector<Entity>& entities) {
        for (const auto& e : entities) {
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
    }

    void drawBuildings(sf::RenderWindow& window, const std::vector<Entity>& buildings) {
        for (const auto& b : buildings) {
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
    }


}

