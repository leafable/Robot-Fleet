//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_SYSTEM_H
#define ROBOT_FLEET_SYSTEM_H
#include <iostream>
#include "Warehouse.h"
#include "TempWarehouse.h"
#include "ObstacleManager.h"

class System {
private:
    Warehouse warehouse;
    TempWarehouse tempWarehouse;
    ObstacleManager obstacles;

    int getSelection(int min, int max, bool bounded);
    int getSelection(int min, int max, bool bounded, const string& text, const string& error);
public:
    System();
    ~System();
    void printWarehouse();
    void printTempWarehouse();
    void runProcess();
};


#endif //ROBOT_FLEET_SYSTEM_H
