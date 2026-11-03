//
// Created by leafy on 10/20/2026.
//

#include "ObstacleManager.h"

#include "Warehouse.h"

int ObstacleManager::warehouseSeed = random_device{}();

// If no seed is provided, pass the randomly generated seed
ObstacleManager::ObstacleManager(const int targetNumObstacles, Warehouse& warehouse) : ObstacleManager(targetNumObstacles, warehouse, warehouseSeed) {}

ObstacleManager::ObstacleManager(const int targetNumObstacles, Warehouse& warehouse, int setSeed) : numSpacesTaken(0) {

    warehouseSeed = setSeed;
    mt19937 seed(setSeed);

    // If the passed value is less than 1, no obstacles are created
    if (targetNumObstacles < 1) {
        return;
    }

    const int maxAttempts = 100;
    int attempts{};

    // Repeat while the size of the vector is less than the target number of obstacles,
    // or until the attempts exceed the max number of attempts
    while (obstacles.size() < targetNumObstacles && attempts < maxAttempts) {
        // Create a candidate obstacle
        Obstacle candidate(warehouse.getWarehouseSize(), seed);

        // If there's overlap, discard the candidate
        if (hasOverlap(candidate)) {
            attempts++;
            continue;
        }

        // Temporarily update the warehouse
        warehouse.updateWarehouse(candidate, true);

        // If the total number of air spaces is greater than the number of air spaces found
        // by the dfs algorithm, then the candidate obstacle is separating the warehouse
        // into islands that the robot cannot cross. Discard the candidate obstacle.
        const auto start = warehouse.findDfsStart();
        numSpacesTaken += candidate.getSize().first * candidate.getSize().second;
        const int numAirSpaces = warehouse.getWarehouseSize() * warehouse.getWarehouseSize() - numSpacesTaken;
        map<pair<int, int>, bool> visited;

        if (start.first == -1 && start.second == -1 || warehouse.dfs(start, visited) < numAirSpaces) {
            attempts++;
            numSpacesTaken -= candidate.getSize().first * candidate.getSize().second;
            warehouse.updateWarehouse(candidate, false);
            continue;
        }

        obstacles.push_back(candidate);
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
    for (const auto& obstacle : obstacles) {
        // Check if the point overlaps the obstacle on the x axis
        if (obstacle.getRightBoundary() >= coord.first && obstacle.getLeftBoundary() <= coord.first) {
            // Check if the point overlaps the obstacle on the y axis
            if (obstacle.getUpperBoundary() >= coord.second && obstacle.getLowerBoundary() <= coord.second) {
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

int ObstacleManager::getSeed() const {
    return warehouseSeed;
}

int ObstacleManager::getNumObstacles() const {
    return obstacles.size();
}