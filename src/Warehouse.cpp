#include "Warehouse.h"
#include <iostream>
#include "Robot.h"
#include "Task.h"
#include <memory>
#include <queue>

char air_symbol = '.';
char obstacle_symbol = '#';

Warehouse::Warehouse(const int size) {
    this->size = size;
    warehouseGrid.assign(size, vector<char>(size, '.'));
}

void Warehouse::drawObstacles(const Obstacle& obstacle, const bool additive) {
    // Additive if mode == 1, subtractive if mode == 0
    const char ch = additive ? obstacle_symbol : air_symbol;

    for (const auto& coord : obstacle.getCoords()) {
        // Check that the coord isn't outside the bounds of the warehouse
        if (isValidPoint(coord)) {
            // Occupy the coord with an obstacle/air depending on the mode
            warehouseGrid[coord.y][coord.x] = ch;
        }
    }
}

bool Warehouse::isValidPoint(const Point& point) const {
    return point >= Point{0, 0} && point < Point{size, size};
}

string Warehouse::getWarehouseStr(const vector<Robot>& robots, const deque<Task>& tasks, const vector<Task>& activeTasks) const {
    stringstream ss;
    vector<vector<char>> grid = warehouseGrid;

    for (const auto& robot : robots) {
        if (isValidPoint(robot.getPosition())) {
            grid[robot.getPosition().y][robot.getPosition().x] = robot.getName();
        }
    }

    for (const auto& task : tasks) {
        if (isValidPoint(task.getPickupPosition()) && !task.getPickupStatus()) {
            grid[task.getPickupPosition().y][task.getPickupPosition().x] = task.getPickupName();
        }
        if (isValidPoint(task.getDropOffPosition()) && !task.getDropOffStatus()) {
            grid[task.getDropOffPosition().y][task.getDropOffPosition().x] = task.getDropOffName();
        }
    }

    for (const auto& task : activeTasks) {
        if (isValidPoint(task.getPickupPosition()) && !task.getPickupStatus()) {
            grid[task.getPickupPosition().y][task.getPickupPosition().x] = task.getPickupName();
        }
        if (isValidPoint(task.getDropOffPosition()) && !task.getDropOffStatus()) {
            grid[task.getDropOffPosition().y][task.getDropOffPosition().x] = task.getDropOffName();
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ss << " " << grid[i][j] << " ";
        }
        // Numbers on the side
        ss << setw(2) << setfill('0') << i + 1 << endl;
    }
    // Numbers at the bottom
    for (int i = 0; i < size; i++) {
        ss << " " << right << setfill('0') << setw(2) << i + 1;
    }
    ss << endl;
    return ss.str();
}

int Warehouse::getWarehouseSize() const {
    return size;
}

const vector<vector<char>> *Warehouse::getWarehouse() const {
    return &warehouseGrid;
}

Point Warehouse::findDfsStart() const {
    // Run through the warehouse vector and find the first air space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (warehouseGrid[j][i] == air_symbol) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int Warehouse::dfs(const Point currentCoord, vector<vector<bool>>& visited) {

    int numSpacesFound = 1;

    // set the current coordinate to visited
    visited[currentCoord.y][currentCoord.x] = true;

    vector<Point> adjacent;

    // find all the spaces adjacent to the current coordinate
    const Point up = {currentCoord.x, currentCoord.y + 1};
    const Point down = {currentCoord.x, currentCoord.y - 1};
    const Point left = {currentCoord.x - 1, currentCoord.y};
    const Point right = {currentCoord.x + 1, currentCoord.y};

    // if the neighboring spaces are valid and are filled with air, push it to the adjacent vector
    if (isValidPoint(up)) {
        if (warehouseGrid[up.y][up.x] == air_symbol) {
            adjacent.push_back(up);
        }
    }
    if (isValidPoint(down)) {
        if (warehouseGrid[down.y][down.x] == air_symbol) {
            adjacent.push_back(down);
        }
    }
    if (isValidPoint(left)) {
        if (warehouseGrid[left.y][left.x] == air_symbol) {
            adjacent.push_back(left);
        }
    }
    if (isValidPoint(right)) {
        if (warehouseGrid[right.y][right.x] == air_symbol) {
            adjacent.push_back(right);
        }
    }

    // Recursively call the dfs function for every unvisited adjacent space
    for (const auto& coord : adjacent) {
        if (!visited[coord.y][coord.x]) {
            numSpacesFound += dfs(coord, visited);
        }
    }
    return numSpacesFound;
}

bool Warehouse::containsObstacle(const Point &coord) const {
    if (isValidPoint(coord)) {
        return warehouseGrid[coord.y][coord.x] != air_symbol;
    }
    cout << "Error: Invalid coordinate (1-" + to_string(size) + ")" << endl;
    return false;
}