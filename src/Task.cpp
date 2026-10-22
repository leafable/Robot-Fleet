#include "Task.h"


    Task::Task(int pickupX, int pickupY, int dropOffX, int dropOffY){
        pickup = {pickupX, pickupY};
        dropOff = {dropOffX, dropOffY};
        robotAssigned = false;
    }

    vector2 Task::getPickupPosition() const{
        return pickup;
    }

    vector2 Task::getDropOffPosition() const{
        return dropOff;
    }

    bool Task::isRobotAssigned() const{
        return robotAssigned;
    }

    void Task::setRobotAssigned(bool robotAssigned){
        this->robotAssigned = robotAssigned;
    }