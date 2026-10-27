//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_ROBOTMANAGER_H
#define ROBOT_FLEET_ROBOTMANAGER_H


class RobotManager {
    public:
    RobotManager();
    ~RobotManager();
    void moveRobot(Robot* r);
    pair<int, int> nextMove(Robot* r)

    private:
    vector<Robot> robots;
};


#endif //ROBOT_FLEET_ROBOTMANAGER_H
