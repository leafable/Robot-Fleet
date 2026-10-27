//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_SYSTEM_H
#define ROBOT_FLEET_SYSTEM_H
#include <iostream>
#include "ObstacleManager.h"
#include "TempWarehouse.h"


class System {
private:
    TempWarehouse tempWarehouse;
public:
    System();
    ~System();
    void printWarehouse();
};


#endif //ROBOT_FLEET_SYSTEM_H
