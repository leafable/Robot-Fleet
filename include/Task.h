#ifndef ROBOT_FLEET_TASK_H
#define ROBOT_FLEET_TASK_H


class Task {
    private:
    vector2 pickup;
    vector2 dropOff;
    bool robotAssigned;

    public:

    Task(int pickupX, int pickupY, int dropOffX, int dropOffY);

    vector2 getPickupPosition();

    vector2 getDropOffPosition();

    bool isRobotAssigned();

    void setRobotAssigned(bool robotAssigned);
};


#endif //ROBOT_FLEET_TASK_H
