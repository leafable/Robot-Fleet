#ifndef ROBOT_FLEET_OBSTACLEMANAGER_H
#define ROBOT_FLEET_OBSTACLEMANAGER_H
#include "Point.h"
#include "Obstacle.h"

using namespace std;

class Warehouse;

class ObstacleManager {
private:
    vector<Obstacle> obstacles;
    int numSpacesTaken;
    bool hasOverlap(const Obstacle& obstacle2) const;
    bool hasOverlap(const Point& coord) const;
    int getNumSpacesTaken() const;
public:
    ObstacleManager(int targetNumObstacles, Warehouse& warehouse, mt19937& seed);
    const vector<Obstacle>* getObstacles() const;
    int getNumObstacles() const;
};


#endif //ROBOT_FLEET_OBSTACLEMANAGER_H
