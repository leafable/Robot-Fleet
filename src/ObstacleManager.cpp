//
// Created by leafy on 10/20/2026.
//

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
}
bool ObstacleManager::hasOverlap(const Obstacle& obstacle2) const {
    for (const auto& obstacle1 : obstacles) {
        // return false if none of the boundaries overlap
        if (obstacle1.getUpperBoundary() < obstacle2.getLowerBoundary() ||
            obstacle1.getLowerBoundary() > obstacle2.getUpperBoundary() ||
            obstacle1.getLeftBoundary() > obstacle2.getRightBoundary() ||
            obstacle1.getRightBoundary() < obstacle2.getLeftBoundary()) {
            return 0;
        }
    }
    return 1;
}
vector<Obstacle> ObstacleManager::getObstacles() {
    return obstacles;
}