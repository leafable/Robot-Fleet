//
// Created by leafy on 10/20/2026.
//

#include "TaskManager.h"

void TaskManager::addTask(const Task& task) {
    taskStack.push_back(task);
}

double TaskManager::getDistance(const Robot& robot, const Task& task, const bool pickup_dropoff) const {

    double x{};
    double y{};

    if (!pickup_dropoff) {
        x = robot.getPosition().x - task.getPickupPosition().x;
        y = robot.getPosition().y - task.getPickupPosition().y;
    }
    else {
        x = robot.getPosition().x - task.getDropoffPosition().x;
        y = robot.getPosition().y - task.getDropoffPosition().y;
    }

    return sqrt(x * x + y * y);
}

Task TaskManager::popTask() {
    if (!taskStack.empty()) {
        Task task = taskStack.front();
        taskStack.erase(taskStack.begin());
        return task;
    }
    return {' ', {-1, -1}, {-1, -1}};
}

int TaskManager::getSize() const {
    return taskStack.size();
}

vector<Task>& TaskManager::getTasks() {
    return taskStack;
}