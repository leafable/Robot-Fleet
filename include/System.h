#ifndef ROBOT_FLEET_SYSTEM_H
#define ROBOT_FLEET_SYSTEM_H
#include <iostream>
#include <random>
#include "Warehouse.h"
#include "ObstacleManager.h"
#include "RobotManager.h"
#include "TaskManager.h"

using namespace std;

class System {
private:
    mt19937 seed;
    static int randomSeed;
    static constexpr int defaultWarehouseSize = 20;
    static constexpr int defaultNumRobots = 3;
    static constexpr int defaultNumTasks = 2;
    Warehouse warehouse;
    ObstacleManager obstacles;
    RobotManager robots;
    TaskManager tasks;

    vector<Point> generateValidCoords(int numCoords);
    bool isValidCoord(const Point& coord) const;
    int getSelection(int min, int max);
    int getSelection(int min, int max, const string& text, const string& error);

public:
    System();
    ~System();
    void printWarehouse();
    void runProcess();
};


#endif //ROBOT_FLEET_SYSTEM_H
