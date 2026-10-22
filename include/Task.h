#ifndef ROBOT_FLEET_TASK_H
#define ROBOT_FLEET_TASK_H
#include <iostream>
#include <vector>
using namespace std;


class Task {
    private:
    vector2 pickup;
    vector2 dropOff;
    bool robotAssigned;

    public:

    Task(int pickupX, int pickupY, int dropOffX, int dropOffY);

    vector2 getPickupPosition() const;

    vector2 getDropOffPosition() const;

    bool isRobotAssigned() const;

    void setRobotAssigned(bool robotAssigned);
};


#endif //ROBOT_FLEET_TASK_H
