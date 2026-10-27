//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_OBSTACLE_H
#define ROBOT_FLEET_OBSTACLE_H
#include <vector>
#include <random>

using namespace std;

class Warehouse;

class Obstacle {
private:
    pair<int, int> origin; // at the top left of the obstacle
    pair<int, int> size; // how far down/right the object extends from the origin
public:
    Obstacle(int warehouseSize);
    pair<int, int> getOrigin() const;
    pair<int, int> getSize() const;
    vector<pair<int, int>> getCoords() const;
    int getLeftBoundary() const;
    int getRightBoundary() const;
    int getUpperBoundary() const;
    int getLowerBoundary() const;
};


#endif //ROBOT_FLEET_OBSTACLE_H
