#ifndef ROBOT_FLEET_TASK_H
#define ROBOT_FLEET_TASK_H
#include "Point.h"

using namespace std;

class Task {
private:
    char pickupName;
    char dropOffName;
    Point pickupPosition;
    Point dropOffPosition;
    bool assigned;
    bool pickupStatus;
    bool dropOffStatus;
public:
    Task();
    Task(char name, const Point &pickup, const Point &dropOff);
    char getPickupName() const;
    char getDropOffName() const;
    Point getPickupPosition() const;
    Point getDropOffPosition() const;
    bool isAssigned() const;
    void setAssigned(bool assigned);
    bool getPickupStatus() const;
    bool getDropOffStatus() const;
    void setPickupStatus(bool pickupStatus);
    void setDropOffStatus(bool dropOffStatus);
};


#endif //ROBOT_FLEET_TASK_H
