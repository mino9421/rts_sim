#pragma once
#include <string>
#include <vector>
#include <optional>
#include <utility>
#include "Entity.h"

int getCost(const std::string& type);
bool isOccupied(int x, int y, const std::vector<Entity>& all);
bool isOccupiedByAny(int x, int y, const std::vector<Entity>& units, const std::vector<Entity>& buildings);
std::optional<std::pair<int, int>> findAdjacentFree(int tx, int ty, const std::vector<Entity>& units, const std::vector<Entity>& buildings);

