//
// Created by admin on 10/20/26.
//

#ifndef ROBOT_FLEET_WAREHOUSE_H
#define ROBOT_FLEET_WAREHOUSE_H

#include <string>
#include <map>
#include <sstream>
#include <vector>

class Obstacle;

using namespace std;

class Warehouse {
private:
    vector<vector<char>> warehouse; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    int size;
public:
    Warehouse(int size);
    void updateWarehouse(const vector<Obstacle>& obstacles);
    string getWarehouseStr(const vector<Obstacle>& obstacles);
    int getWarehouseSize() const;
    const vector<vector<char>> *getWarehouse() const;
};


#endif //ROBOT_FLEET_WAREHOUSE_H
