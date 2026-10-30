//
// Created by admin on 10/20/26.
//

#ifndef ROBOT_FLEET_TEMPWAREHOUSE_H
#define ROBOT_FLEET_TEMPWAREHOUSE_H

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class TempWarehouse {
private:
    vector<vector<char>> tempWarehouse; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    vector<vector<bool>> obstacles = {
        {0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {1, 1, 0, 0, 0}
    };
    int size;
public:
    TempWarehouse(int size);
    string getTempWarehouseStr();
    int getTempWarehouseSize() const;
    const vector<vector<char>> *getTempWarehouse() const;
};


#endif //ROBOT_FLEET_WAREHOUSE_H
