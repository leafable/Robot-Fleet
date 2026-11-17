#ifndef ROBOT_FLEET_TASK_H
#define ROBOT_FLEET_TASK_H
#include "Warehouse.h"
#include "Point.h"

class TaskManager;

using namespace std;

class Task {
private:
    char pickupName;
    char dropoffName;
    Point pickup;
    Point dropoff;
public:
    Task();
    Task(char startName, const Warehouse& warehouse, mt19937& seed);
    Task(char startName, const Point &pickup, const Point &dropoff);
    void setPickupName(char name);
    void setDropoffName(char name);
    void setPickupPosition(const Point& coord);
    void setDropoffPosition(const Point& coord);
    char getPickupName() const;
    char getDropoffName() const;
    Point getPickupPosition() const;
    Point getDropoffPosition() const;
};


#endif //ROBOT_FLEET_TASK_H
