//
// Created by leafy on 10/20/2026.
//

#include <iostream>
#include "../include/ObstacleManager.h"

ObstacleManager::ObstacleManager(int targetNumObstacles) {

    // if the passed value is less than 1, no obstacles are created
    if (targetNumObstacles < 1) {
        return;
    }

    int maxAttempts = 100;
    int attempts{};

    // create an obstacle so the loop has something to compare to
    obstacles.push_back(Obstacle());

    while (obstacles.size() < targetNumObstacles && attempts < maxAttempts) {
        Obstacle candidate;

        // check if the candidate has any overlaps
        if (hasOverlap(candidate)) {
            attempts++;
            continue;
        }

        obstacles.push_back(candidate);
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
        if (obstacle1.getUpperBoundary() < obstacle2.getLowerBoundary() && obstacle1.getLowerBoundary() > obstacle2.getUpperBoundary()) {
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