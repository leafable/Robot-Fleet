//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_OBSTACLEMANAGER_H
#define ROBOT_FLEET_OBSTACLEMANAGER_H
#include <iostream>
#include <map>
#include "Obstacle.h"

class Warehouse;

class ObstacleManager {
private:
    vector<Obstacle> obstacles;
    static int numSpacesTaken;
public:
    ObstacleManager(int num, Warehouse& warehouse);
    bool hasOverlap(const Obstacle &obstacle2) const;
    const vector<Obstacle> *getObstacles() const;
    void printAllCoords() const; // for debugging purposes, do not use
    pair<int, int> findDfsStart(const Warehouse& warehouse);
    int dfs(pair<int, int> currentCoord, map<pair<int, int>, bool>& visited, const Warehouse& warehouse); // https://www.geeksforgeeks.org/dsa/depth-first-search-or-dfs-for-a-graph/
    static int getNumSpacesTaken();
};


#endif //ROBOT_FLEET_OBSTACLEMANAGER_H
