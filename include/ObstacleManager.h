//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_OBSTACLEMANAGER_H
#define ROBOT_FLEET_OBSTACLEMANAGER_H
#include "Obstacle.h"
#include "Point.h"

class Warehouse;

class ObstacleManager {
private:
    vector<Obstacle> obstacles;
    int numSpacesTaken;
public:
    ObstacleManager(int targetNumObstacles, Warehouse& warehouse);
    ObstacleManager(int targetNumObstacles, Warehouse& warehouse, int setSeed);
    bool hasOverlap(const Obstacle& obstacle2) const;
    bool hasOverlap(const Point& coord) const;
    const vector<Obstacle>* getObstacles() const;
    int getNumSpacesTaken() const;
    int getNumObstacles() const;
};


#endif //ROBOT_FLEET_OBSTACLEMANAGER_H
