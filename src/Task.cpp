#include "Task.h"
#include "TaskManager.h"
#include <random>

Task::Task() {
    this->pickupName = ' ';
    this->dropoffName = ' ';
    this->pickup = {-1, -1};
    this->dropoff = {-1, -1};
}

Task::Task(char startName, const Point &pickup, const Point &dropoff){
    this->pickupName = startName;
    this->dropoffName = startName + 1;
    this->pickup = pickup;
    this->dropoff = dropoff;
}

Task::Task(char startName, const Warehouse& warehouse, mt19937& seed){
    this->pickupName = startName;
    this->dropoffName = startName + 1;

    // Roll for a valid pickupCoord
    Point pickupCoord;
    do {
        uniform_int_distribution<int> pickupX(0, warehouse.getWarehouseSize() - 1);
        uniform_int_distribution<int> pickupY(0, warehouse.getWarehouseSize() - 1);
        pickupCoord = {pickupX(seed), pickupY(seed)};
    } while (!warehouse.isAir(pickupCoord));
    this->pickup = pickupCoord;

    // Roll for a valid dropoffCoord
    Point dropoffCoord;
    do {
        uniform_int_distribution<int> dropoffX(0, warehouse.getWarehouseSize() - 1);
        uniform_int_distribution<int> dropoffY(0, warehouse.getWarehouseSize() - 1);
        dropoffCoord = {dropoffX(seed), dropoffY(seed)};
    } while (!warehouse.isAir(dropoffCoord));
    this->dropoff = dropoffCoord;
}

char Task::getPickupName() const {
    return pickupName;
}

char Task::getDropoffName() const {
    return dropoffName;
}

Point Task::getPickupPosition() const{
    return pickup;
}

Point Task::getDropoffPosition() const{
    return dropoff;
}

void Task::setPickupPosition(const Point& coord) {
    this->pickup = coord;
}

void Task::setDropoffPosition(const Point& coord) {
    this->dropoff = coord;
}

void Task::setPickupName(const char name) {
    this->pickupName = name;
}

void Task::setDropoffName(const char name) {
    this->dropoffName = name;
}
