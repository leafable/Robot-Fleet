//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_OBSTACLEMANAGER_H
#define ROBOT_FLEET_OBSTACLEMANAGER_H
#include "Obstacle.h"

class ObstacleManager {
private:
    vector<Obstacle> obstacles;
    vector<pair<int, int>> origins;
    vector<pair<int, int>> sizes;
    vector<vector<pair<int, int>>> coordinates;
public:
    ObstacleManager(int num);
    bool hasOverlap(const Obstacle &obstacle2) const;
    const vector<Obstacle> *getObstacles() const;
    void printAllCoords() const; // for debugging purposes, do not use
};


#endif //ROBOT_FLEET_OBSTACLEMANAGER_H
