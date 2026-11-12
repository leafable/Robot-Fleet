#ifndef ROBOT_FLEET_TASK_H
#define ROBOT_FLEET_TASK_H
#include <iostream>
#include "Warehouse.h"
#include "Point.h"

using namespace std;

class Task {
private:
    char name;
    Point pickup;
    Point dropoff;
public:
    Task(char name, const Warehouse &warehouse);
    Task(char name, const Point &pickup, const Point &dropoff);
    char getName() const;
    Point getPickupPosition() const;
    Point getDropoffPosition() const;
};


#endif //ROBOT_FLEET_TASK_H
