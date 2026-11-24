#ifndef ROBOT_FLEET_WAREHOUSE_H
#define ROBOT_FLEET_WAREHOUSE_H
#include <deque>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Point.h"
#include "Obstacle.h"
#include "Robot.h"

using namespace std;

class Warehouse {
private:
    vector<vector<char>> warehouseGrid; // https://www.geeksforgeeks.org/cpp/different-ways-to-initialize-a-map-in-cpp/
    int size;
public:
    Warehouse(int size);
    ~Warehouse() = default;
    void drawObstacles(const Obstacle& obstacle, bool additive);
    string getWarehouseStr(const vector<Robot>& robots, const deque<Task>& tasks, const vector<Task>& activeTasks) const;
    bool isValidPoint(const Point &point) const;
    Point findDfsStart() const;
    int dfs(Point currentCoord, vector<vector<bool>>& visited);
    bool containsObstacle(const Point &coord) const;
    int getWarehouseSize() const;
    const vector<vector<char>> *getWarehouse() const;
};


#endif //ROBOT_FLEET_WAREHOUSE_H
