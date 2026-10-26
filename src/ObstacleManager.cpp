//
// Created by leafy on 10/20/2026.
//

#include "../include/ObstacleManager.h"

#include "Warehouse.h"

int ObstacleManager::numSpacesTaken = 0;

ObstacleManager::ObstacleManager(int targetNumObstacles, Warehouse& warehouse) {

    // if the passed value is less than 1, no obstacles are created
    if (targetNumObstacles < 1) {
        return;
    }

    int maxAttempts = 100;
    int attempts{};

    // create an obstacle so the loop has something to compare to
    // obstacles.push_back(Obstacle());

    while (obstacles.size() < targetNumObstacles && attempts < maxAttempts) {
        Obstacle candidate(warehouse.getWarehouseSize());

        if (hasOverlap(candidate)) {
            attempts++;
            continue;
        }

        obstacles.push_back(candidate);
        warehouse.updateWarehouse(obstacles);

        auto start = findDfsStart(warehouse);
        numSpacesTaken += candidate.getSize().first * candidate.getSize().second;
        int numAirSpaces = warehouse.getWarehouseSize() * warehouse.getWarehouseSize() - numSpacesTaken;
        map<pair<int, int>, bool> visited;

        if (start.first == -1 && start.second == -1 || dfs(start, visited, warehouse) < numAirSpaces) {
            attempts++;
            numSpacesTaken -= candidate.getSize().first * candidate.getSize().second;
            obstacles.pop_back();
            warehouse.updateWarehouse(obstacles);
            continue;
        }

        warehouse.updateWarehouse(obstacles);
        attempts = 0;
    }

    if (attempts) {
        cerr << "Unable to create all " << targetNumObstacles << " obstacles." << endl;
    }
}
bool ObstacleManager::hasOverlap(const Obstacle& obstacle2) const {
    for (const auto& obstacle1 : obstacles) {
        bool overlapX{};
        bool overlapY{};
        if (obstacle1.getRightBoundary() > obstacle2.getLeftBoundary() && obstacle1.getLeftBoundary() < obstacle2.getRightBoundary()) {
            overlapX = 1;
        }
        if (obstacle1.getUpperBoundary() > obstacle2.getLowerBoundary() && obstacle1.getLowerBoundary() < obstacle2.getUpperBoundary()) {
            overlapY = 1;
        }
        if (overlapX && overlapY) {
            return 1;
        }
    }
    return 0;
}

const vector<Obstacle> *ObstacleManager::getObstacles() const {
    return &obstacles;
}

void ObstacleManager::printAllCoords() const {
    for (const auto& obstacle : obstacles) {
        for (const auto& coord : obstacle.getCoords())
        cout << "(" << coord.first << ", " << coord.second << ")" << endl;
    }
}

pair<int, int> ObstacleManager::findDfsStart(const Warehouse& warehouse) {
    for (int i = 0; i < warehouse.getWarehouseSize(); i++) {
        for (int j = 0; j < warehouse.getWarehouseSize(); j++) {
            if (warehouse.getWarehouse()->at(i).at(j) == '.') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int ObstacleManager::dfs(pair<int, int> currentCoord, map<pair<int, int>, bool>& visited, const Warehouse& warehouse) {

    int numSpacesFound = 1;

    // set the current coordinate to visited
    visited[currentCoord] = true;

    vector<pair<int, int>> adjacent;

    // find all the spaces adjacent to the current coordinate
    pair<int, int> up = {currentCoord.first, currentCoord.second + 1};
    pair<int, int> down = {currentCoord.first, currentCoord.second - 1};
    pair<int, int> left = {currentCoord.first - 1, currentCoord.second};
    pair<int, int> right = {currentCoord.first + 1, currentCoord.second};

    // if the neighboring spaces are valid and are filled with air, push it to the adjacent vector
    if (up.first >= 0 && up.second >= 0 && up.first < warehouse.getWarehouseSize() && up.second < warehouse.getWarehouseSize()) {
        if (warehouse.getWarehouse()->at(up.first).at(up.second) == '.') {
            adjacent.push_back(up);
        }
    }
    if (down.first >= 0 && down.second >= 0 && down.first < warehouse.getWarehouseSize() && down.second < warehouse.getWarehouseSize()) {
        if (warehouse.getWarehouse()->at(down.first).at(down.second) == '.') {
            adjacent.push_back(down);
        }
    }
    if (left.first >= 0 && left.second >= 0 && left.first < warehouse.getWarehouseSize() && left.second < warehouse.getWarehouseSize()) {
        if (warehouse.getWarehouse()->at(left.first).at(left.second) == '.') {
            adjacent.push_back(left);
        }
    }
    if (right.first >= 0 && right.second >= 0 && right.first < warehouse.getWarehouseSize() && right.second < warehouse.getWarehouseSize()) {
        if (warehouse.getWarehouse()->at(right.first).at(right.second) == '.') {
            adjacent.push_back(right);
        }
    }

    for (auto& i : adjacent) {
        if (!visited[i]) {
            numSpacesFound += dfs(i, visited, warehouse);
        }
    }
    return numSpacesFound;
}

int ObstacleManager::getNumSpacesTaken() {
    return numSpacesTaken;
}