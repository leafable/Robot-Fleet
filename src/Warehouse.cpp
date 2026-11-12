//
// Created by admin on 10/20/26.
//

#include "Warehouse.h"

#include <map>

#include "Robot.h"
#include "Task.h"

char air_symbol = '.';
char obstacle_symbol = '#';

int Warehouse::warehouseSeed = random_device{}();

Warehouse::Warehouse(int size) {
    this->size = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            warehouse.resize(size);
            warehouse.at(i).push_back(air_symbol);
        }
    }
}

void Warehouse::drawObstacles(const Obstacle& obstacle, bool additive) {
    // Additive if mode == 1, subtractive if mode == 0
    char ch = additive ? obstacle_symbol : air_symbol;

    for (const auto& coord : obstacle.getCoords()) {
        // Check that the coord isn't outside the bounds of the warehouse
        if (coord.x < size && coord.y < size) {
            // Occupy the coord with an obstacle/air depending on the mode
            warehouse[coord.x][coord.y] = ch;
        }
    }
}

void Warehouse::drawRobots(vector<Robot>& robots) {
    for (auto& robot : robots) {
        if (robot.peekPath().x == -1 || robot.peekPath().y == -1) {
            warehouse.at(robot.getPosition().x).at(robot.getPosition().y) = robot.getName();
        }
    }
}

void Warehouse::updateRobots(vector<Robot>& robots) {
    for (auto& robot : robots) {
        warehouse.at(robot.getPosition().x).at(robot.getPosition().y) = air_symbol;
        robot.moveRobot();
        warehouse.at(robot.getPosition().x).at(robot.getPosition().y) = robot.getName();
    }
}

void Warehouse::drawTasks(vector<Task>& tasks) {
    for (auto& task : tasks) {
        warehouse.at(task.getPickupPosition().x).at(task.getPickupPosition().y) = task.getName();
        warehouse.at(task.getDropoffPosition().x).at(task.getDropoffPosition().y) = task.getName();
    }
}

string Warehouse::getWarehouseStr() {
    stringstream ss;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            ss << " " << warehouse[i][j] << " ";
        }
        ss << setw(2) << setfill('0') << i + 1 << endl;
    }
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
    return &warehouse;
}

Point Warehouse::findDfsStart() {
    // Run through the warehouse vector and find the first air space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (warehouse.at(i).at(j) == air_symbol) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int Warehouse::dfs(Point currentCoord, map<Point, bool>& visited) {

    int numSpacesFound = 1;

    // set the current coordinate to visited
    visited[currentCoord] = true;

    vector<Point> adjacent;

    // find all the spaces adjacent to the current coordinate
    Point up = {currentCoord.x, currentCoord.y + 1};
    Point down = {currentCoord.x, currentCoord.y - 1};
    Point left = {currentCoord.x - 1, currentCoord.y};
    Point right = {currentCoord.x + 1, currentCoord.y};

    // if the neighboring spaces are valid and are filled with air, push it to the adjacent vector
    if (up.x >= 0 && up.y >= 0 && up.x < size && up.y < size) {
        if (warehouse.at(up.x).at(up.y) == air_symbol) {
            adjacent.push_back(up);
        }
    }
    if (down.x >= 0 && down.y >= 0 && down.x < size && down.y < size) {
        if (warehouse.at(down.x).at(down.y) == air_symbol) {
            adjacent.push_back(down);
        }
    }
    if (left.x >= 0 && left.y >= 0 && left.x < size && left.y < size) {
        if (warehouse.at(left.x).at(left.y) == air_symbol) {
            adjacent.push_back(left);
        }
    }
    if (right.x >= 0 && right.y >= 0 && right.x < size && right.y < size) {
        if (warehouse.at(right.x).at(right.y) == air_symbol) {
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

bool Warehouse::isAir(Point coord) const {
    if (coord.x < size && coord.y < size) {
        return (warehouse.at(coord.x).at(coord.y) == air_symbol);
    }
    else {
        cout << "Error: Invalid coordinate (1-" + to_string(size) + ")" << endl;
        return false;
    }
}

int Warehouse::getWarehouseSeed() const {
    return warehouseSeed;
}

void Warehouse::setWarehouseSeed(int warehouseSeed) {
    this->warehouseSeed = warehouseSeed;
}