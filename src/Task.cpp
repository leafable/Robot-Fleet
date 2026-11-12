#include "Task.h"

#include <random>

Task::Task(const char name, const Warehouse& warehouse) {
    mt19937 seed(warehouse.getWarehouseSeed());

    this->name = name;

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

Task::Task(const char name, const Point &pickup, const Point &dropoff) {
    this->name = name;
    this->pickup = pickup;
    this->dropoff = dropoff;
}

char Task::getName() const {
    return name;
}

Point Task::getPickupPosition() const{
    return pickup;
}

Point Task::getDropoffPosition() const{
    return dropoff;
}