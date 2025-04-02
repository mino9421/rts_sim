// HudSystem.cpp
#include "HudSystem.h"
#include "GameConfig.h"
#include <sstream>

void HudSystem::drawHUD(sf::RenderWindow& window, const GameState& state) {
    static sf::Font font;
    static bool fontLoaded = false;

    if (!fontLoaded) {
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"); // adjust if needed
        fontLoaded = true;
    }

    // Draw credits top-left
    sf::Text creditText;
    creditText.setFont(font);
    creditText.setCharacterSize(16);
    creditText.setFillColor(sf::Color::White);
    creditText.setPosition(10.f, 5.f);

    std::ostringstream ss;
    ss << "Credits: " << state.credits;
    creditText.setString(ss.str());
    window.draw(creditText);

    // Bottom action bar
    sf::Text actionText;
    actionText.setFont(font);
    actionText.setCharacterSize(16);
    actionText.setFillColor(sf::Color::Cyan);
    actionText.setPosition(10.f, MAP_HEIGHT * TILE_SIZE - 28);

    for (const auto& b : state.buildings) {
        if (b.selected) {
            if (b.type == "Barracks")
                actionText.setString("Press [S] to produce Soldier (200)");
            else if (b.type == "CommandCenter")
                actionText.setString("Press [B] to produce Builder (1000)");
        }
    }
    
    for (const auto& e : state.entities) {
        if (e.selected && e.type == "Builder") {
            actionText.setString("Press [B] to build Barracks (800), [H] to build Depot (2000)");
        }
    }
    

    window.draw(actionText);
}
