//
// Created by admin on 10/20/26.
//

#include "../include/Warehouse.h"

Warehouse::Warehouse(int size) {
    this->size = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            warehouse[{i, j}] = '.';
        }
    }
}
void Warehouse::updateWarehouse(const ObstacleManager& obstacles) {
    for (const auto& obstacle : *obstacles.getObstacles()) {
        for (const auto& coord : obstacle.getCoords()) {
            warehouse[coord] = '#';
        }
    }
}
string Warehouse::getWarehouseStr(const ObstacleManager& obstacles) {
    stringstream ss;
    updateWarehouse(obstacles);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ss << " " << warehouse[{i, j}] << " ";
        }
        ss << endl;
    }
    return ss.str();
}