#ifndef ROBOT_FLEET_ROBOTMANAGER_H
#define ROBOT_FLEET_ROBOTMANAGER_H
#include <utility>
#include <vector>

class Robot;

class RobotManager {
public:
    RobotManager();
    RobotManager(int n);
    ~RobotManager() = default;

    void addRobot(Robot &r);
    void moveRobot();
    std::pair<int, int> nextMove(Robot &r);
    const std::vector<Robot>& getRobots() const;

private:
    std::vector<Robot> robots;
    int numRobots;
};


#endif //ROBOT_FLEET_ROBOTMANAGER_H