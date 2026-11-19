#include "RobotManager.h"
#include "Robot.h"
#include "Warehouse.h"

// RobotManager::RobotManager(const Warehouse& warehouse, mt19937& seed) {
//     Point coords;
//     do {
//         uniform_int_distribution<int> coordX(0, warehouse.getWarehouseSize() - 1);
//         uniform_int_distribution<int> coordY(0, warehouse.getWarehouseSize() - 1);
//         coords = {coordX(seed), coordY(seed)};
//     } while (!warehouse.isAir(coords));
//     Robot r = Robot('1', 100, coords, "Idle");
//     robots.push_back(r);
//     numRobots = 1;
// }

RobotManager::RobotManager(const Warehouse& warehouse, mt19937& seed, const int n) {
    addRobot(warehouse, seed, n);
    numRobots = n;
}

void RobotManager::addRobot(const Warehouse& warehouse, mt19937& seed, const int n) {
    for (int i = 0; i < n; i++) {
        Point coords;
        do {
            uniform_int_distribution<int> coordX(0, warehouse.getWarehouseSize() - 1);
            uniform_int_distribution<int> coordY(0, warehouse.getWarehouseSize() - 1);
            coords = {coordX(seed), coordY(seed)};
        } while (!warehouse.isAir(coords));
        robots.emplace_back(robots.empty() ? '1' : robots.back().getName() + 1, 100, coords, "Idle");
    }
    numRobots = robots.size();
}

void RobotManager::removeRobot(const int n) {
    for (int i = 0; i < n && robots.size() > 1; i++) {
        robots.pop_back();
    }
    numRobots = robots.size();
}

// void RobotManager::moveRobot(const int steps) {
//     for (int i = 0; i < steps; i++) {
//         robots[index].setPosition(robots[index].peekPath());
//         robots[index].popPath();
//         robots[index].setStatus("active");
//         robots[index].setBattery((robots[index].getBattery()-2));
//         if (robots[index].isPathEmpty()) {
//             robots[index].setStatus("Idle");
//         }
//     }
// }

// std::pair<int, int> RobotManager::nextMove(Robot& r) {
//     return r.peekPath();
// }

std::vector<Robot>& RobotManager::getRobots() {
    return robots;
}

int RobotManager::getNumRobots() const {
    return numRobots;
}