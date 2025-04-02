#pragma once
#include <string>
#include <queue>

struct Entity {
    std::string type;
    int x, y;
    int team = 1;
    int targetX = -1, targetY = -1;
    bool selected = false;
    bool isBuilding = false;
    float buildTimer = 0.0f;
    int buildOnX = -1, buildOnY = -1;
    std::string buildQueued;
    std::queue<std::string> productionQueue;
    float productionTimer = 0.0f;
    float harvestTimer = 0.0f;
};

