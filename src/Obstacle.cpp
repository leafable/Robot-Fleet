//
// Created by leafy on 10/20/2026.
//

#include "Obstacle.h"
#include "Warehouse.h"

Obstacle::Obstacle(int warehouseSize, mt19937& seed) {
    //https://en.cppreference.com/cpp/numeric/random/uniform_int_distribution
    uniform_int_distribution<int> sizeX(1, 5);
    uniform_int_distribution<int> sizeY(1, 5);
    size.x = sizeX(seed);
    size.y = sizeY(seed);
    uniform_int_distribution<int> originX(0, warehouseSize - size.x);
    uniform_int_distribution<int> originY(0, warehouseSize - size.y);
    origin.x = originX(seed);
    origin.y = originY(seed);
}
Point Obstacle::getOrigin() const {
    return origin;
}
Point Obstacle::getSize() const {
    return size;
}
vector<Point> Obstacle::getCoords() const {
    vector<Point> coords;
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            coords.push_back({origin.x + i, origin.y + j});
        }
    }
    return coords;
}
int Obstacle::getLeftBoundary() const {
    return origin.x;
}
int Obstacle::getRightBoundary() const {
    return origin.x + size.x - 1;
}
int Obstacle::getLowerBoundary() const {
    return origin.y;
}
int Obstacle::getUpperBoundary() const {
    return origin.y + size.y - 1;
}