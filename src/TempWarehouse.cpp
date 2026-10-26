//
// Created by admin on 10/20/26.
//

#include "../include/TempWarehouse.h"
#include "ObstacleManager.h"

TempWarehouse::TempWarehouse(int size) {
    this->size = size;
    warehouse.resize(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (obstacles.at(i).at(j) == 0)
                warehouse.at(i).push_back('.');
            else
                warehouse.at(i).push_back('#');
        }
    }
}

string TempWarehouse::getTempWarehouseStr() {
    stringstream ss;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ss << " " << warehouse[i][j] << " ";
        }
        ss << endl;
    }
    return ss.str();
}

int TempWarehouse::getTempWarehouseSize() const {
    return size;
}

const vector<vector<char>> *TempWarehouse::getTempWarehouse() const {
    return &warehouse;
}