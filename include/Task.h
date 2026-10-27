#ifndef ROBOT_FLEET_TASK_H
#define ROBOT_FLEET_TASK_H
#include <iostream>
#include <vector>
using namespace std;


class Task {
    private:
    pair<int, int> pickup;
    pair<int, int> dropOff;
    bool robotAssigned;

    public:

    Task(int pickupX, int pickupY, int dropOffX, int dropOffY);

    pair<int, int> getPickupPosition() const;

    pair<int, int> getDropOffPosition() const;

    bool isRobotAssigned() const;

    void setRobotAssigned(bool robotAssigned);
};


#endif //ROBOT_FLEET_TASK_H
