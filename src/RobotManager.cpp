#include "../include/RobotManager.h"

#include "Robot.h"
#include "Warehouse.h"

RobotManager::RobotManager(const Warehouse& warehouse) {
    Point coords;
    mt19937 seed(warehouse.getWarehouseSeed() + 1);
    do {
        uniform_int_distribution<int> coordX(0, warehouse.getWarehouseSize() - 1);
        uniform_int_distribution<int> coordY(0, warehouse.getWarehouseSize() - 1);
        coords = {coordX(seed), coordY(seed)};
    } while (!warehouse.isAir(coords));
    Robot r = Robot('1', 100, coords, "idle");
    robots.push_back(r);
    numRobots = 1;
}

RobotManager::RobotManager(const Warehouse& warehouse, const int n) {
    Point coords;
    mt19937 seed(warehouse.getWarehouseSeed() + 1);
    for (int i = 0; i < n; i++) {
        do {
            uniform_int_distribution<int> coordX(0, warehouse.getWarehouseSize() - 1);
            uniform_int_distribution<int> coordY(0, warehouse.getWarehouseSize() - 1);
            coords = {coordX(seed), coordY(seed)};
        } while (!warehouse.isAir(coords));
        int name = '1';
        Robot r = Robot(name + i, 100, coords, "idle");
        robots.push_back(r);
    }
    numRobots = n;
}

void RobotManager::addRobot(const Robot& r) {
    robots.push_back(r);
    numRobots++;
}


// void RobotManager::moveRobot(const int steps) {
//     for (int i = 0; i < steps; i++) {
//         robots[index].setPosition(robots[index].peekPath());
//         robots[index].popPath();
//         robots[index].setStatus("active");
//         robots[index].setBattery((robots[index].getBattery()-2));
//         if (robots[index].isPathEmpty()) {
//             robots[index].setStatus("idle");
//         }
//     }
// }

// std::pair<int, int> RobotManager::nextMove(Robot& r) {
//     return r.peekPath();
// }

std::vector<Robot>& RobotManager::getRobots() {
    return robots;
}