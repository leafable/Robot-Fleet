#ifndef ROBOT_FLEET_ROBOTMANAGER_H
#define ROBOT_FLEET_ROBOTMANAGER_H
#include <vector>
#include "Point.h"

class Robot;
class Warehouse;

class RobotManager {
public:
    RobotManager(const Warehouse& warehouse);
    RobotManager(const Warehouse& warehouse, int n);
    ~RobotManager() = default;
    void addRobot(const Robot &r);
    void moveRobot(int index, int steps);
    Point nextMove(Robot &r);
    std::vector<Robot>& getRobots();

private:
    std::vector<Robot> robots;
    int numRobots;
};


#endif //ROBOT_FLEET_ROBOTMANAGER_H