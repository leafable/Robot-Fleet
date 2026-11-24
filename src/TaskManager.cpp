#include "TaskManager.h"

void TaskManager::addTask(vector<Point> coords) {
    // Point pickupCoord;
    // Point dropOffCoord;
    //
    // for (int i = 0; i < numTasks; i++) {
    //     // Roll for a valid pickupCoord
    //     do {
    //         uniform_int_distribution<int> pickupX(0, warehouse.getWarehouseSize() - 1);
    //         uniform_int_distribution<int> pickupY(0, warehouse.getWarehouseSize() - 1);
    //         pickupCoord = {pickupX(seed), pickupY(seed)};
    //     } while (!warehouse.containsObstacle(pickupCoord) || containsTask(pickupCoord));
    //
    //     // Roll for a valid dropOffCoord
    //     do {
    //         uniform_int_distribution<int> dropoffX(0, warehouse.getWarehouseSize() - 1);
    //         uniform_int_distribution<int> dropoffY(0, warehouse.getWarehouseSize() - 1);
    //         dropOffCoord = {dropoffX(seed), dropoffY(seed)};
    //     } while (!warehouse.containsObstacle(dropOffCoord) || dropOffCoord == pickupCoord || containsTask(dropOffCoord));
    //
    //     taskQueue.emplace_back(startName + 2 * i, pickupCoord, dropOffCoord);
    // }

    for (int i = 0; i + 1 < coords.size(); i += 2) {
        if (coords[i] != Point{-1, -1} && coords[i + 1] != Point{-1, -1}) {
            char name = 'A';
            // If the tasks queue is not empty, it will always have the highest character name
            if (!taskQueue.empty()) {
                name = static_cast<char>(taskQueue.back().getDropOffName() + 1);
            }
            else if (!activeTasks.empty()) {
                name = static_cast<char>(activeTasks.back().getDropOffName() + 1);
            }
            taskQueue.emplace_back(name > 'Z' ? 'A' : name, coords[i], coords[i + 1]);
        }
    }

}

void TaskManager::addTask(const Point &pickup, const Point &dropOff) {
    taskQueue.emplace_back(!taskQueue.empty() ? static_cast<char>(taskQueue.back().getDropOffName() + 1) : 'A', pickup, dropOff);
}

// void TaskManager::updateTask(const Robot& robot, const int robotIndex) {
//     if (robot.getPosition() == taskQueue[robotIndex].getPickupPosition()) {
//         taskQueue[robotIndex].setPickupStatus(true);
//     }
//     if (robot.getPosition() == taskQueue[robotIndex].getDropOffPosition() && taskQueue[robotIndex].getPickupPosition() == Point{-1, -1}) {
//         taskQueue[robotIndex].setDropOffStatus(true);
//     }
// }

bool TaskManager::containsTask(const Point& coord) const {
    for (const auto& task : taskQueue) {
        if (task.getPickupPosition() == coord || task.getDropOffPosition() == coord) {
            return true;
        }
    }
    for (const auto& task : activeTasks) {
        if (task.getPickupPosition() == coord || task.getDropOffPosition() == coord) {
            return true;
        }
    }
    return false;
}

// double TaskManager::getDistance(const Robot& robot, const Task& task, const bool pickup_dropOff) const {
//
//     double x{};
//     double y{};
//
//     if (!pickup_dropOff) {
//         x = robot.getPosition().x - task.getPickupPosition().x;
//         y = robot.getPosition().y - task.getPickupPosition().y;
//     }
//     else {
//         x = robot.getPosition().x - task.getDropOffPosition().x;
//         y = robot.getPosition().y - task.getDropOffPosition().y;
//     }
//
//     return sqrt(x * x + y * y);
// }

Task TaskManager::popTask() {
    if (!taskQueue.empty()) {
        const Task task = taskQueue.front();
        taskQueue.pop_front();
        return task;
    }
    return {};
}

// bool TaskManager::assignTask(const int index, const int numRobots) {
//     // If the current index is not assigned, assign it
//     if (!taskQueue[index].isAssigned()) {
//         taskQueue[index].setAssigned(true);
//         return true;
//     }
//     // If the size of the queue is less than or equal to the number
//     // of robots, then there are no queued tasks
//     if (taskQueue.size() <= numRobots) {
//         return false;
//     }
//     // Check if there are any unassigned queued tasks
//     for (int i = numRobots; i < taskQueue.size(); i++) {
//         if (!taskQueue[i].isAssigned()) {
//             swap(taskQueue[i], taskQueue[index]);
//             taskQueue[index].setAssigned(true);
//             taskQueue.erase(taskQueue.begin() + i);
//             return true;
//         }
//     }
//     return false;
// }

int TaskManager::getSize() const {
    return taskQueue.size();
}

deque<Task> &TaskManager::getQueuedTasks() {
    return taskQueue;
}

vector<Task> &TaskManager::getActiveTasks() {
    return activeTasks;
}

vector<int> &TaskManager::getNoTasksCounter() {
    return noTasksCounter;
}
