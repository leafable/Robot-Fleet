//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_OBSTACLE_H
#define ROBOT_FLEET_OBSTACLE_H
#include <vector>
#include <random>
#include "Point.h"

using namespace std;

class Warehouse;

class Obstacle {
private:

    Point origin; // at the top left of the obstacle
    Point size; // how far down/right the object extends from the origin
public:
    Obstacle(int warehouseSize, mt19937& seed);
    Point getOrigin() const;
    Point getSize() const;
    vector<Point> getCoords() const;
    int getLeftBoundary() const;
    int getRightBoundary() const;
    int getUpperBoundary() const;
    int getLowerBoundary() const;
};


#endif //ROBOT_FLEET_OBSTACLE_H
