#ifndef ROBOT_FLEET_WAREHOUSE_H
#define ROBOT_FLEET_WAREHOUSE_H

#include <deque>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <memory>

#include "ObstacleManager.h"
#include "RobotManager.h"
#include "Point.h"

class Obstacle;
class Robot;
class Task;

using namespace std;

class Warehouse {
private:
    vector<vector<char>> warehouseGrid; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    vector<vector<char>> robotsGrid;
    vector<vector<char>> tasksGrid;
    int size;
public:
    Warehouse(int size);
    void drawObstacles(const Obstacle& obstacle, bool additive);
    void drawRobots(const vector<Robot> &robots);
    void updateRobot(Robot &robot, Task& task);
    void drawTasks(const deque<Task> & tasks, vector<Task> &activeTasks);

    void updateTask(const Robot &robot, Task &task);

    string getWarehouseStr();
    int getWarehouseSize() const;

    const vector<vector<char>> *getWarehouse() const;

    Point findDfsStart();
    int dfs(Point currentCoord, map<Point, bool>& visited);
    bool isAir(Point) const;
};


#endif //ROBOT_FLEET_WAREHOUSE_H
