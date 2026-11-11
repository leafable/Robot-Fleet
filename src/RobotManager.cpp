#include "../include/RobotManager.h"
#include "../include/Robot.h"

RobotManager::RobotManager() {
    Robot r = Robot('A', 100, {0, 0}, "idle");
    robots.push_back(r);
    numRobots = 1;
}

RobotManager::RobotManager(int n) {
    for (int i = 0; i < n; i++) {
        char c = 65 + i;
        Robot r = Robot(c, 100, {0, i}, "idle");
        robots.push_back(r);
    }
    numRobots = n;
}

void RobotManager::addRobot(Robot& r) {
    robots.push_back(r);
    numRobots++;
}


void RobotManager::moveRobot() {
    for(int i = 0; i < robots.size(); i++) {
        robots[i].setPositon(robots[i].peekPath());
        robots[i].popPath();
        robots[i].setStatus("active");
        robots[i].setBattery((robots[i].getBattery()-2));
        if (robots[i].isPathEmpty()) {
            robots[i].setStatus("idle");
        }
    }
}

std::pair<int, int> RobotManager::nextMove(Robot& r) {
    return r.peekPath();
}

const std::vector<Robot>& RobotManager::getRobots() const {
    return robots;
}