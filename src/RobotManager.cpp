#include "RobotManager.h"
#include "Robot.h"

void RobotManager::addRobot(vector<Point> coords) {
    // for (int i = 0; i < n; i++) {
    //     Point coord;
    //     do {
    //         uniform_int_distribution<int> coordX(0, warehouse.getWarehouseSize() - 1);
    //         uniform_int_distribution<int> coordY(0, warehouse.getWarehouseSize() - 1);
    //         coord = {coordX(seed), coordY(seed)};
    //     } while (warehouse.containsObstacle(coord) || containsRobot(coord));
    //     robots.emplace_back(robots.empty() ? '1' : robots.back().getName() + 1, 100, coord, "Idle");
    // }

    for (int i = 0; i < coords.size(); i++) {
        if (coords[i] != Point{-1, -1}) {
            robots.emplace_back(!robots.empty() ? static_cast<char>(robots.back().getName() + 1) : '1', 100, coords[i], "Idle");
        }
    }
}

bool RobotManager::containsRobot(const Point& coord) const {
    for (const auto& robot : robots) {
        if (robot.getPosition() == coord) {
            return true;
        }
    }
    return false;
}

void RobotManager::removeRobot(const int n) {
    for (int i = 0; i < n && robots.size() > 1; i++) {
        robots.pop_back();
    }
}

std::vector<Robot>& RobotManager::getRobots() {
    return robots;
}

int RobotManager::getNumRobots() const {
    return robots.size();
}