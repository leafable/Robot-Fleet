//
// Created by admin on 10/20/26.
//

#ifndef ROBOT_FLEET_WAREHOUSE_H
#define ROBOT_FLEET_WAREHOUSE_H

#include <string>
#include <map>
#include <sstream>
#include "ObstacleManager.h"

using namespace std;

class Warehouse {
private:
    map<pair<int, int>, char> warehouse; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    int size;
public:
    Warehouse(int size);
    void updateWarehouse(const ObstacleManager& obstacles);
    string getWarehouseStr(const ObstacleManager& obstacles);
};


#endif //ROBOT_FLEET_WAREHOUSE_H
