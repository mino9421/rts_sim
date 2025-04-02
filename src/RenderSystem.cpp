// RenderSystem.cpp - Handles rendering logic
#include "RenderSystem.h"
#include <SFML/Graphics.hpp>
#include "GameConfig.h"
#include "Entity.h"
#include "GameState.h"

namespace RenderSystem {

    const sf::Color playerColor = sf::Color::Green;
    const sf::Color enemyColor  = sf::Color::Red;

    void drawHUD(sf::RenderWindow& window, const GameState& state) {
        static sf::Font font;
        static bool loaded = font.loadFromFile("assets/arial.ttf");
    
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

    void drawEntities(sf::RenderWindow& window, const std::vector<Entity>& entities, const sf::Font& font) {
        for (const auto& e : entities) {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            shape.setPosition(e.x * TILE_SIZE, e.y * TILE_SIZE);
            shape.setFillColor(e.team == 1 ? playerColor : enemyColor);

            if (e.selected) {
                shape.setOutlineColor(sf::Color::Yellow);
                shape.setOutlineThickness(2);
            } else {
                shape.setOutlineThickness(0); // no outline
            }
        
            window.draw(shape);
        
            // 🔹 Draw letter marker
            sf::Text label;
            label.setFont(font);
            label.setCharacterSize(20);
            label.setFillColor(sf::Color(200, 50, 255)); // soft bright purple
            label.setString(
                e.type == "Builder" ? "b" :
                e.type == "Soldier" ? "s" : "?"
            );
            sf::FloatRect textRect = label.getLocalBounds();
            label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            label.setPosition(e.x * TILE_SIZE + TILE_SIZE / 2.0f, e.y * TILE_SIZE + TILE_SIZE / 2.0f);

            window.draw(label);
        }        
    }

    void drawBuildings(sf::RenderWindow& window, const std::vector<Entity>& buildings, const sf::Font& font) {
        for (const auto& b : buildings) {
            sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            shape.setPosition(b.x * TILE_SIZE, b.y * TILE_SIZE);
            shape.setFillColor(b.team == 1 ? playerColor : enemyColor);

            if (b.selected) {
                shape.setOutlineColor(sf::Color::Yellow);
                shape.setOutlineThickness(2);
            } else {
                shape.setOutlineThickness(0);
            }
            
        
            window.draw(shape);
        
            // 🔹 Draw letter marker
            sf::Text label;
            label.setFont(font);
            label.setCharacterSize(20);
            label.setFillColor(sf::Color(200, 50, 255)); // soft bright purple
            label.setStyle(sf::Text::Bold);
            label.setString(
                b.type == "CommandCenter" ? "C" :
                b.type == "Barracks"       ? "B" :
                b.type == "Depot"          ? "D" : "?"
            );
            sf::FloatRect textRect = label.getLocalBounds();
            label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            label.setPosition(b.x * TILE_SIZE + TILE_SIZE / 2.0f, b.y * TILE_SIZE + TILE_SIZE / 2.0f);

            window.draw(label);
        }        
    }

}
