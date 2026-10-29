//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_TASKMANAGER_H
#define ROBOT_FLEET_TASKMANAGER_H
#include <iostream>
#include "Task.h"
using namespace std;


class TaskManager {
    private:
    vector<Task> queue;
    public:
    TaskManager();
    void addTask(pair<int, int> pickup, pair<int, int> dropoff);
    bool taskOverlap()
};


#endif //ROBOT_FLEET_TASKMANAGER_H
