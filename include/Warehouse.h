//
// Created by admin on 10/20/26.
//

#ifndef ROBOT_FLEET_WAREHOUSE_H
#define ROBOT_FLEET_WAREHOUSE_H

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>

#include "ObstacleManager.h"
#include "RobotManager.h"
#include "Point.h"

class Obstacle;
class Robot;
class Task;

using namespace std;

class Warehouse {
private:
    vector<vector<char>> warehouse; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    static int warehouseSeed;
    int size;
public:
    Warehouse(int size);
    void drawObstacles(const Obstacle& obstacle, bool additive);

    void drawRobots(vector<Robot> &robots);

    void updateRobots(vector<Robot>& robots);
    void drawTasks(vector<Task> &tasks);
    string getWarehouseStr();
    int getWarehouseSize() const;
    const vector<vector<char>> *getWarehouse() const;
    Point findDfsStart();
    int dfs(Point currentCoord, map<Point, bool>& visited);
    bool isAir(Point) const;
    int getWarehouseSeed() const;
    void setWarehouseSeed(int warehouseSeed);
};


#endif //ROBOT_FLEET_WAREHOUSE_H
