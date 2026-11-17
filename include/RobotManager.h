#ifndef ROBOT_FLEET_ROBOTMANAGER_H
#define ROBOT_FLEET_ROBOTMANAGER_H
#include <random>
#include <vector>

class Robot;
class Warehouse;

class RobotManager {
public:
    RobotManager(const Warehouse& warehouse, std::mt19937& seed);
    RobotManager(const Warehouse& warehouse, std::mt19937& seed, int n);
    ~RobotManager() = default;
    void addRobot(const Robot &r);
    // void moveRobot(int index, int steps);
    // Point nextMove(Robot &r);
    std::vector<Robot>& getRobots();
    int getNumRobots() const;

private:
    std::vector<Robot> robots;
    int numRobots;
};


#endif //ROBOT_FLEET_ROBOTMANAGER_H