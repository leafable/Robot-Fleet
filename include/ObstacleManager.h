//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_OBSTACLEMANAGER_H
#define ROBOT_FLEET_OBSTACLEMANAGER_H
#include <iostream>
#include <map>
#include "Obstacle.h"

class Warehouse;

class ObstacleManager {
private:
    vector<Obstacle> obstacles;
    int warehouseSeed = static_cast<int>(random_device{}());
    int numSpacesTaken;
public:
    ObstacleManager(int targetNumObstacles, Warehouse& warehouse);
    ObstacleManager(int targetNumObstacles, Warehouse& warehouse, int setSeed);
    bool hasOverlap(const Obstacle& obstacle2) const;
    bool hasOverlap(const pair<int,int>& coord) const;
    const vector<Obstacle>* getObstacles() const;
    int getNumSpacesTaken() const;
    int getSeed() const;
    int getNumObstacles() const;
};


#endif //ROBOT_FLEET_OBSTACLEMANAGER_H
