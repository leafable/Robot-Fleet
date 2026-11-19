#include "Warehouse.h"
#include <iostream>
#include "Robot.h"
#include "Task.h"
#include <map>
#include <memory>
#include <queue>

char air_symbol = '.';
char obstacle_symbol = '#';

Warehouse::Warehouse(int size) {
    this->size = size;
    robotsGrid.resize(size);
    tasksGrid.resize(size);
    for (int i = 0; i < size; i++) {
        warehouseGrid.emplace_back(size, '.');
        robotsGrid.at(i).resize(size);
        tasksGrid.at(i).resize(size);
    }
}

void Warehouse::drawObstacles(const Obstacle& obstacle, const bool additive) {
    // Additive if mode == 1, subtractive if mode == 0
    const char ch = additive ? obstacle_symbol : air_symbol;

    for (const auto& coord : obstacle.getCoords()) {
        // Check that the coord isn't outside the bounds of the warehouse
        if (coord.x >= 0 && coord.y >= 0 && coord.x < size && coord.y < size) {
            // Occupy the coord with an obstacle/air depending on the mode
            warehouseGrid[coord.y][coord.x] = ch;
        }
    }
}

void Warehouse::drawRobots(const vector<Robot>& robots) {
    robotsGrid.clear();
    robotsGrid.resize(size);
    for (int i = 0; i < size; i++) {
        robotsGrid.at(i).resize(size);
    }

    for (auto& robot : robots) {
        // Check bounds
        if (robot.getPosition().x >= 0 && robot.getPosition().y >= 0 &&
            robot.getPosition().x < size && robot.getPosition().y < size)
        {
            robotsGrid.at(robot.getPosition().y).at(robot.getPosition().x) = robot.getName();
        }
    }
}

void Warehouse::updateRobot(Robot &robot, Task& task) {
    // robotsGrid.clear();
    // robotsGrid.resize(size);
    // for (int i = 0; i < size; i++) {
    //     robotsGrid.at(i).resize(size);
    // }

    // Check bounds
    if (robot.getPosition().x >= 0 && robot.getPosition().y >= 0 &&
        robot.getPosition().x < size && robot.getPosition().y < size)
    {
        robotsGrid.at(robot.getPosition().y).at(robot.getPosition().x) = '\0';
        robot.moveRobot(task);
        robotsGrid.at(robot.getPosition().y).at(robot.getPosition().x) = robot.getName();
    }
}

void Warehouse::drawTasks(const deque<Task> &tasks, const vector<Task> &activeTasks) {
    tasksGrid.clear();
    tasksGrid.resize(size);
    for (int i = 0; i < size; i++) {
        tasksGrid.at(i).resize(size);
    }

    for (auto& task : tasks) {
        // Check bounds
        if (task.getPickupPosition().x >= 0 && task.getPickupPosition().y >= 0 &&
            task.getDropoffPosition().x >= 0 && task.getDropoffPosition().y >= 0 &&
            task.getPickupPosition().x < size && task.getPickupPosition().y < size &&
            task.getDropoffPosition().x < size && task.getDropoffPosition().y < size)
        {
            tasksGrid.at(task.getPickupPosition().y).at(task.getPickupPosition().x) = task.getPickupName();
            tasksGrid.at(task.getDropoffPosition().y).at(task.getDropoffPosition().x) = task.getDropoffName();
        }
    }

    for (auto& task : activeTasks) {
        // Check bounds
        if (task.getPickupPosition().x >= 0 && task.getPickupPosition().y >= 0 &&
            task.getPickupPosition().x < size && task.getPickupPosition().y < size)
        {
            tasksGrid.at(task.getPickupPosition().y).at(task.getPickupPosition().x) = task.getPickupName();
        }
        // Check bounds
        if (task.getDropoffPosition().x >= 0 && task.getDropoffPosition().y >= 0 &&
            task.getDropoffPosition().x < size && task.getDropoffPosition().y < size)
        {
            tasksGrid.at(task.getDropoffPosition().y).at(task.getDropoffPosition().x) = task.getDropoffName();
        }
    }
}

void Warehouse::updateTask(const Robot& robot, Task &task) {
    // tasksGrid.clear();
    // tasksGrid.resize(size);
    // for (int i = 0; i < size; i++) {
    //     tasksGrid.at(i).resize(size);
    // }

    if (robot.getPosition() == task.getPickupPosition()) {
        task.setPickupPosition({-1, -1});
        // task.setPickupName(' ');
    }
    if (robot.getPosition() == task.getDropoffPosition() && task.getPickupPosition() == Point{-1, -1}) {
        task.setDropoffPosition({-1, -1});
        // task.setDropoffName(' ');
    }
}

string Warehouse::getWarehouseStr() {
    stringstream ss;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (robotsGrid[i][j] != '\0') {
                ss << " " << robotsGrid[i][j] << " ";
            }
            else if (tasksGrid[i][j] != '\0') {
                ss << " " << tasksGrid[i][j] << " ";
            }
            else {
                ss << " " << warehouseGrid[i][j] << " ";
            }
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

Point Warehouse::findDfsStart() {
    // Run through the warehouse vector and find the first air space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (warehouseGrid.at(j).at(i) == air_symbol) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int Warehouse::dfs(const Point currentCoord, map<Point, bool>& visited) {

    int numSpacesFound = 1;

    // set the current coordinate to visited
    visited[currentCoord] = true;

    vector<Point> adjacent;

    // find all the spaces adjacent to the current coordinate
    const Point up = {currentCoord.x, currentCoord.y + 1};
    const Point down = {currentCoord.x, currentCoord.y - 1};
    const Point left = {currentCoord.x - 1, currentCoord.y};
    const Point right = {currentCoord.x + 1, currentCoord.y};

    // if the neighboring spaces are valid and are filled with air, push it to the adjacent vector
    if (up.x >= 0 && up.y >= 0 && up.x < size && up.y < size) {
        if (warehouseGrid.at(up.y).at(up.x) == air_symbol) {
            adjacent.push_back(up);
        }
    }
    if (down.x >= 0 && down.y >= 0 && down.x < size && down.y < size) {
        if (warehouseGrid.at(down.y).at(down.x) == air_symbol) {
            adjacent.push_back(down);
        }
    }
    if (left.x >= 0 && left.y >= 0 && left.x < size && left.y < size) {
        if (warehouseGrid.at(left.y).at(left.x) == air_symbol) {
            adjacent.push_back(left);
        }
    }
    if (right.x >= 0 && right.y >= 0 && right.x < size && right.y < size) {
        if (warehouseGrid.at(right.y).at(right.x) == air_symbol) {
            adjacent.push_back(right);
        }
    }

    // Recursively call the dfs function for every unvisited adjacent space
    for (auto& i : adjacent) {
        if (!visited[i]) {
            numSpacesFound += dfs(i, visited);
        }
    }
    return numSpacesFound;
}

bool Warehouse::isAir(const Point coord) const {
    if (coord.x >= 0 && coord.y >= 0 && coord.x < size && coord.y < size) {
        return warehouseGrid.at(coord.y).at(coord.x) == air_symbol && robotsGrid.at(coord.y).at(coord.x) == '\0' && tasksGrid.at(coord.y).at(coord.x) == '\0';
    }
    cout << "Error: Invalid coordinate (1-" + to_string(size) + ")" << endl;
    return false;
}