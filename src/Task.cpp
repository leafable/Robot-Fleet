#include "Task.h"

Task::Task() {
    this->pickupName = ' ';
    this->dropOffName = ' ';
    this->pickupPosition = {-1, -1};
    this->dropOffPosition = {-1, -1};
    this->assigned = false;
    this->pickupStatus = false;
    this->dropOffStatus = false;
}

Task::Task(const char name, const Point &pickup, const Point &dropOff){
    this->pickupName = name;
    this->dropOffName = static_cast<char>(name + 1);
    this->pickupPosition = pickup;
    this->dropOffPosition = dropOff;
    this->assigned = false;
    this->pickupStatus = false;
    this->dropOffStatus = false;
}

// Task::Task(const char startName, const Warehouse& warehouse, mt19937& seed){
//     this->pickupName = startName;
//     this->dropOffName = startName + 1;
//     this->assigned = false;
//     this->pickupStatus = false;
//     this->dropOffStatus = false;
//
//     // Roll for a valid pickupCoord
//     Point pickupCoord;
//     do {
//         uniform_int_distribution<int> pickupX(0, warehouse.getWarehouseSize() - 1);
//         uniform_int_distribution<int> pickupY(0, warehouse.getWarehouseSize() - 1);
//         pickupCoord = {pickupX(seed), pickupY(seed)};
//     } while (!warehouse.isAir(pickupCoord));
//     this->pickupPosition = pickupCoord;
//
//     // Roll for a valid dropOffCoord
//     Point dropOffCoord;
//     do {
//         uniform_int_distribution<int> dropoffX(0, warehouse.getWarehouseSize() - 1);
//         uniform_int_distribution<int> dropoffY(0, warehouse.getWarehouseSize() - 1);
//         dropOffCoord = {dropoffX(seed), dropoffY(seed)};
//     } while (!warehouse.isAir(dropOffCoord) || dropOffCoord == pickupCoord);
//     this->dropOffPosition = dropOffCoord;
// }

char Task::getPickupName() const {
    return pickupName;
}

char Task::getDropOffName() const {
    return dropOffName;
}

Point Task::getPickupPosition() const{
    return pickupPosition;
}

Point Task::getDropOffPosition() const{
    return dropOffPosition;
}

// void Task::setPickupPosition(const Point& coord) {
//     this->pickupPosition = coord;
// }
//
// void Task::setDropOffPosition(const Point& coord) {
//     this->dropOffPosition = coord;
// }

bool Task::isAssigned() const {
    return assigned;
}

void Task::setAssigned(bool assigned) {
    this->assigned = assigned;
}

bool Task::getPickupStatus() const {
    return pickupStatus;
}

bool Task::getDropOffStatus() const {
    return dropOffStatus;
}

void Task::setPickupStatus(bool pickupStatus) {
    this->pickupStatus = pickupStatus;
}

void Task::setDropOffStatus(bool dropOffStatus) {
    this->dropOffStatus = dropOffStatus;
}

// void Task::setPickupName(const char name) {
//     this->pickupName = name;
// }
//
// void Task::setDropoffName(const char name) {
//     this->dropoffName = name;
// }
