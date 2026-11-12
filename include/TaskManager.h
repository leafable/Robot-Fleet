//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_TASKMANAGER_H
#define ROBOT_FLEET_TASKMANAGER_H

#include <vector>
#include "Task.h"
#include "Robot.h"

class TaskManager {
private:
    vector<Task> taskStack;
public:
    TaskManager() = default;
    ~TaskManager() = default;
    void addTask(const Task& task);
    double getDistance(const Robot& robot, const Task& task, bool pickup_dropoff) const;
    Task popTask();
    int getSize() const;
    vector<Task>& getTasks();
};


#endif //ROBOT_FLEET_TASKMANAGER_H
