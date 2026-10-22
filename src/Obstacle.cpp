//
// Created by leafy on 10/20/2026.
//

#include "../include/Obstacle.h"

Obstacle::Obstacle() {
    random_device rd; //https://en.cppreference.com/cpp/numeric/random/uniform_int_distribution
    mt19937 gen(rd());
    uniform_int_distribution<int> sizeX(2, 4);
    uniform_int_distribution<int> sizeY(2, 4);
    size.first = sizeX(gen);
    size.second = sizeY(gen);
    uniform_int_distribution<int> originX(0, 20 - size.first);
    uniform_int_distribution<int> originY(0, 20 - size.second);
    origin.first = originX(gen);
    origin.second = originY(gen);
}
pair<int, int> Obstacle::getOrigin() const {
    return origin;
}
pair<int, int> Obstacle::getSize() const {
    return size;
}
vector<pair<int, int>> Obstacle::getCoords() const {
    vector<pair<int, int>> coords;
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            coords.push_back({origin.first + i, origin.second + j});
        }
    }
    return coords;
}
int Obstacle::getLeftBoundary() const {
    return origin.first;
}
int Obstacle::getRightBoundary() const {
    return origin.first + size.first;
}
int Obstacle::getUpperBoundary() const {
    return origin.second;
}
int Obstacle::getLowerBoundary() const {
    return origin.second + size.second;
}