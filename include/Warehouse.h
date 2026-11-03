//
// Created by admin on 10/20/26.
//

#ifndef ROBOT_FLEET_WAREHOUSE_H
#define ROBOT_FLEET_WAREHOUSE_H

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "ObstacleManager.h"
#include "RobotManager.h"

class Obstacle;

using namespace std;

class Warehouse {
private:
    vector<vector<char>> warehouse; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    int size;
    int time;
public:
    Warehouse(int size);
    void updateWarehouse(const Obstacle& obstacle, bool additive);
    void updateWarehouse(const vector<Robot>& robots, int steps);
    string getWarehouseStr();
    int getWarehouseSize() const;
    const vector<vector<char>> *getWarehouse() const;
    pair<int, int> findDfsStart();
    int dfs(pair<int, int> currentCoord, map<pair<int, int>, bool>& visited);
};


#endif //ROBOT_FLEET_WAREHOUSE_H
