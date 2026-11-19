#ifndef ROBOT_FLEET_SYSTEM_H
#define ROBOT_FLEET_SYSTEM_H
#include <iostream>
#include "Warehouse.h"
#include "ObstacleManager.h"
#include "TaskManager.h"

class System {
private:
    mt19937 seed;
    static int randomSeed;
    static int numRobots;
    static int numTasks;
    Warehouse warehouse;
    ObstacleManager obstacles;
    RobotManager robots;
    TaskManager tasks;

    vector<Task> activeTasks;
    vector<int> noTasksCounter;

    int getSelection(int min, int max);
    int getSelection(int min, int max, const string& text, const string& error);

public:
    System();
    ~System();
    void printWarehouse();
    void runProcess();
};


#endif //ROBOT_FLEET_SYSTEM_H
