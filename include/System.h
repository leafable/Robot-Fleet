//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_SYSTEM_H
#define ROBOT_FLEET_SYSTEM_H
#include <iostream>
#include "ObstacleManager.h"


class System {
private:
    ObstacleManager obstacles;
public:
    System();
    ~System();
};


#endif //ROBOT_FLEET_SYSTEM_H
