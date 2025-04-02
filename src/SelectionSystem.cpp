#include "SelectionSystem.h"

namespace SelectionSystem {

void selectUnitsInBox(const sf::Vector2f& start, const sf::Vector2f& end, std::vector<Entity>& entities) {
    sf::FloatRect selectionBox(
        std::min(start.x, end.x),
        std::min(start.y, end.y),
        std::abs(end.x - start.x),
        std::abs(end.y - start.y)
    );

    for (auto& e : entities) {
        if (e.type == "Soldier" || e.type == "Builder") {
            sf::FloatRect unitBox(e.x * 32, e.y * 32, 32, 32);
            e.selected = selectionBox.intersects(unitBox);
        }
    }
}

void drawSelectionBox(sf::RenderWindow& window, bool isSelecting, const sf::Vector2f& start, const sf::Vector2f& current) {
    if (!isSelecting) return;

    sf::RectangleShape box;
    box.setFillColor(sf::Color(0, 255, 0, 50));
    box.setOutlineColor(sf::Color::Green);
    box.setOutlineThickness(1);

    sf::Vector2f size(
        std::abs(current.x - start.x),
        std::abs(current.y - start.y)
    );
    box.setSize(size);
    box.setPosition(
        std::min(start.x, current.x),
        std::min(start.y, current.y)
    );

    window.draw(box);
}

} // namespace
