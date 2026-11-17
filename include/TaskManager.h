#ifndef ROBOT_FLEET_TASKMANAGER_H
#define ROBOT_FLEET_TASKMANAGER_H

#include "Task.h"
#include "Robot.h"

class TaskManager {
private:
    deque<Task> taskQueue;
public:
    TaskManager() = default;
    TaskManager(char startName, const Warehouse& warehouse, mt19937& seed, int numTasks);
    ~TaskManager() = default;
    void addTask(const Task& task);
    double getDistance(const Robot& robot, const Task& task, bool pickup_dropoff) const;
    Task popTask();
    Task peekTask() const;
    int getSize() const;
    deque<Task> &getTasks();
};


#endif //ROBOT_FLEET_TASKMANAGER_H
