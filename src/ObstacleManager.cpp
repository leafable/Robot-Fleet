//
// Created by leafy on 10/20/2026.
//

#include "ObstacleManager.h"

#include "Warehouse.h"

// By default, randomly generate a seed
int ObstacleManager::warehouseSeed = random_device{}();

// If no seed is provided, pass the randomly generated seed
ObstacleManager::ObstacleManager(const int targetNumObstacles, Warehouse& warehouse) : ObstacleManager(targetNumObstacles, warehouse, warehouseSeed) {}

ObstacleManager::ObstacleManager(const int targetNumObstacles, Warehouse& warehouse, const int setSeed) : numSpacesTaken(0) {

    mt19937 seed(setSeed);

    // if the passed value is less than 1, no obstacles are created
    if (targetNumObstacles < 1) {
        return;
    }

    const int maxAttempts = 100;
    int attempts{};

    // create an obstacle so the loop has something to compare to
    // obstacles.push_back(Obstacle());

    while (obstacles.size() < targetNumObstacles && attempts < maxAttempts) {
        Obstacle candidate(warehouse.getWarehouseSize(), seed);

        if (hasOverlap(candidate)) {
            attempts++;
            continue;
        }

        obstacles.push_back(candidate);
        warehouse.updateWarehouse(obstacles);

        const auto start = warehouse.findDfsStart();
        numSpacesTaken += candidate.getSize().first * candidate.getSize().second;
        const int numAirSpaces = warehouse.getWarehouseSize() * warehouse.getWarehouseSize() - numSpacesTaken;
        map<pair<int, int>, bool> visited;

        if (start.first == -1 && start.second == -1 || warehouse.dfs(start, visited) < numAirSpaces) {
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
        cout << "Unable to create all " << targetNumObstacles << " obstacles." << endl;
    }
}

bool ObstacleManager::hasOverlap(const Obstacle& obstacle2) const {
    for (const auto& obstacle1 : obstacles) {
        // Check if the obstacles overlap on the x axis
        if (obstacle1.getRightBoundary() >= obstacle2.getLeftBoundary() && obstacle1.getLeftBoundary() <= obstacle2.getRightBoundary()) {
            // Check if the obstacles overlap on the y axis
            if (obstacle1.getUpperBoundary() >= obstacle2.getLowerBoundary() && obstacle1.getLowerBoundary() <= obstacle2.getUpperBoundary()) {
                return 1;
            }
        }
    }
    return 0;
}

bool ObstacleManager::hasOverlap(const pair<int,int>& coord) const {
    for (const auto& obstacle1 : obstacles) {
        // Check if the point overlaps the obstacle on the x axis
        if (obstacle1.getRightBoundary() >= coord.first && obstacle1.getLeftBoundary() <= coord.first) {
            // Check if the point overlaps the obstacle on the y axis
            if (obstacle1.getUpperBoundary() >= coord.second && obstacle1.getLowerBoundary() <= coord.second) {
                return 1;
            }
        }
    }
    return 0;
}

const vector<Obstacle>* ObstacleManager::getObstacles() const {
    return &obstacles;
}

int ObstacleManager::getNumSpacesTaken() const {
    return numSpacesTaken;
}

int ObstacleManager::getSeed() {
    return warehouseSeed;
}

int ObstacleManager::getNumObstacles() const {
    return obstacles.size();
}

// pair<int, int> ObstacleManager::findDfsStart(const Warehouse& warehouse) {
//     // Run through the warehouse vector and find the first air space
//     for (int i = 0; i < warehouse.getWarehouseSize(); i++) {
//         for (int j = 0; j < warehouse.getWarehouseSize(); j++) {
//             if (warehouse.getWarehouse()->at(i).at(j) == '.') {
//                 return {i, j};
//             }
//         }
//     }
//     return {-1, -1};
// }

// int ObstacleManager::dfs(pair<int, int> currentCoord, map<pair<int, int>, bool>& visited, const Warehouse& warehouse) {
//
//     int numSpacesFound = 1;
//
//     // set the current coordinate to visited
//     visited[currentCoord] = true;
//
//     vector<pair<int, int>> adjacent;
//
//     // find all the spaces adjacent to the current coordinate
//     pair<int, int> up = {currentCoord.first, currentCoord.second + 1};
//     pair<int, int> down = {currentCoord.first, currentCoord.second - 1};
//     pair<int, int> left = {currentCoord.first - 1, currentCoord.second};
//     pair<int, int> right = {currentCoord.first + 1, currentCoord.second};
//
//     // if the neighboring spaces are valid and are filled with air, push it to the adjacent vector
//     if (up.first >= 0 && up.second >= 0 && up.first < warehouse.getWarehouseSize() && up.second < warehouse.getWarehouseSize()) {
//         if (warehouse.getWarehouse()->at(up.first).at(up.second) == '.') {
//             adjacent.push_back(up);
//         }
//     }
//     if (down.first >= 0 && down.second >= 0 && down.first < warehouse.getWarehouseSize() && down.second < warehouse.getWarehouseSize()) {
//         if (warehouse.getWarehouse()->at(down.first).at(down.second) == '.') {
//             adjacent.push_back(down);
//         }
//     }
//     if (left.first >= 0 && left.second >= 0 && left.first < warehouse.getWarehouseSize() && left.second < warehouse.getWarehouseSize()) {
//         if (warehouse.getWarehouse()->at(left.first).at(left.second) == '.') {
//             adjacent.push_back(left);
//         }
//     }
//     if (right.first >= 0 && right.second >= 0 && right.first < warehouse.getWarehouseSize() && right.second < warehouse.getWarehouseSize()) {
//         if (warehouse.getWarehouse()->at(right.first).at(right.second) == '.') {
//             adjacent.push_back(right);
//         }
//     }
//
//     for (auto& i : adjacent) {
//         if (!visited[i]) {
//             numSpacesFound += dfs(i, visited, warehouse);
//         }
//     }
//     return numSpacesFound;
// }