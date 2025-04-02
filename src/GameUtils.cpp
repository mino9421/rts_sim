#include "GameUtils.h"

int getCost(const std::string& type) {
    if (type == "Soldier") return 200;
    if (type == "Builder") return 1000;
    if (type == "Barracks") return 800;
    if (type == "Depot") return 2000;
    return 0;
}

bool isOccupied(int x, int y, const std::vector<Entity>& all) {
    for (const auto& e : all) {
        if (e.x == x && e.y == y)
            return true;
    }
    return false;
}

bool isOccupiedByAny(int x, int y, const std::vector<Entity>& units, const std::vector<Entity>& buildings) {
    return isOccupied(x, y, units) || isOccupied(x, y, buildings);
}

std::optional<std::pair<int, int>> findAdjacentFree(int tx, int ty, const std::vector<Entity>& units, const std::vector<Entity>& buildings) {
    std::vector<std::pair<int, int>> offsets = {
        {0, -1}, {0, 1}, {-1, 0}, {1, 0}
    };
    for (auto [dx, dy] : offsets) {
        int nx = tx + dx;
        int ny = ty + dy;
        if (nx >= 0 && nx < 20 && ny >= 0 && ny < 15 && !isOccupiedByAny(nx, ny, units, buildings)) {
            return std::make_pair(nx, ny);
        }
    }
    return std::nullopt;
}

