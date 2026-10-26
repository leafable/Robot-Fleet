//
// Created by admin on 10/20/26.
//

#include "../include/Warehouse.h"
#include "ObstacleManager.h"

Warehouse::Warehouse(int size) {
    this->size = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            warehouse.resize(size);
            warehouse.at(i).push_back('.');
        }
    }
}
void Warehouse::updateWarehouse(const vector<Obstacle>& obstacles) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            warehouse[i][j] = '.';
        }
    }

    for (const auto& obstacle : obstacles) {
        for (const auto& coord : obstacle.getCoords()) {
            warehouse[coord.first][coord.second] = '#';
        }
    }
}
string Warehouse::getWarehouseStr(const vector<Obstacle>& obstacles) {
    stringstream ss;
    updateWarehouse(obstacles);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ss << " " << warehouse[i][j] << " ";
        }
        ss << endl;
    }
    return ss.str();
}

int Warehouse::getWarehouseSize() const {
    return size;
}

const vector<vector<char>> *Warehouse::getWarehouse() const {
    return &warehouse;
}