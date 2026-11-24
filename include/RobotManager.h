#ifndef ROBOT_FLEET_ROBOTMANAGER_H
#define ROBOT_FLEET_ROBOTMANAGER_H
#include <vector>
#include "Point.h"
#include "Robot.h"

class RobotManager {
public:
    RobotManager() = default;
    ~RobotManager() = default;
    void addRobot(std::vector<Point> coords);
    void removeRobot(int n);
    bool containsRobot(const Point &coord) const;
    std::vector<Robot>& getRobots();
    int getNumRobots() const;

private:
    std::vector<Robot> robots;
};


#endif //ROBOT_FLEET_ROBOTMANAGER_H