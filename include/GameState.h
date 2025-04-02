// GameState.h
#pragma once
#include <vector>
#include <string>
#include "Entity.h"

struct GameState {
    std::vector<Entity> entities = { {"Builder", 6, 5} };
    std::vector<Entity> buildings = { {"CommandCenter", 5, 5} };
    bool buildMode = false;
    std::string buildTypeQueued = "";
    int credits = 10000;
};