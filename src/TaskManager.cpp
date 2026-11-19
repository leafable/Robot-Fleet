#include "TaskManager.h"
#include <memory>

TaskManager::TaskManager(char startName, const Warehouse& warehouse, mt19937& seed, const int numTasks) {
    for (int i = 0; i < numTasks; i++) {
        addTask(Task(startName + 2 * i, warehouse, seed));
    }
}

void TaskManager::addTask(const Task& task) {
    taskQueue.push_back(task);
}

// double TaskManager::getDistance(const Robot& robot, const Task& task, const bool pickup_dropoff) const {
//
//     double x{};
//     double y{};
//
//     if (!pickup_dropoff) {
//         x = robot.getPosition().x - task.getPickupPosition().x;
//         y = robot.getPosition().y - task.getPickupPosition().y;
//     }
//     else {
//         x = robot.getPosition().x - task.getDropoffPosition().x;
//         y = robot.getPosition().y - task.getDropoffPosition().y;
//     }
//
//     return sqrt(x * x + y * y);
// }

Task TaskManager::popTask() {
    if (!taskQueue.empty()) {
        Task task = taskQueue.front();
        taskQueue.pop_front();
        return task;
    }
    return {};
}

int TaskManager::getSize() const {
    return taskQueue.size();
}

deque<Task> &TaskManager::getTasks() {
    return taskQueue;
}