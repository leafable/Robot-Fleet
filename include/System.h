//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_SYSTEM_H
#define ROBOT_FLEET_SYSTEM_H
#include <iostream>
#include "ObstacleManager.h"
#include "Warehouse.h"


class System {
private:
    ObstacleManager obstacles;
    Warehouse warehouse;
public:
    System();
    ~System();
    void printWarehouse();
    void printAllCoords(); // for debugging purposes, do not use
};


#endif //ROBOT_FLEET_SYSTEM_H
