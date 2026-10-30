//
// Created by admin on 10/20/26.
//

#include "Warehouse.h"

Warehouse::Warehouse(int size) {
    this->size = size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            warehouse.resize(size);
            warehouse.at(i).push_back('.');
        }
    }
}
void Warehouse::updateWarehouse(const vector<Obstacle>& obstacles) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            warehouse[i][j] = '.';
        }
    }

    for (const auto& obstacle : obstacles) {
        for (const auto& coord : obstacle.getCoords()) {
            // Check that the coord isn't outside the bounds of the warehouse
            if (coord.first < size && coord.second < size) {
                // Occupy the coord with an obstacle
                warehouse[coord.first][coord.second] = '#';
            }
        }
    }
}
string Warehouse::getWarehouseStr(const vector<Obstacle>& obstacles) {
    stringstream ss;
    updateWarehouse(obstacles);
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

pair<int, int> Warehouse::findDfsStart() {
    // Run through the warehouse vector and find the first air space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (warehouse.at(i).at(j) == '.') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int Warehouse::dfs(pair<int, int> currentCoord, map<pair<int, int>, bool>& visited) {

    int numSpacesFound = 1;

    // set the current coordinate to visited
    visited[currentCoord] = true;

    vector<pair<int, int>> adjacent;

    // find all the spaces adjacent to the current coordinate
    pair<int, int> up = {currentCoord.first, currentCoord.second + 1};
    pair<int, int> down = {currentCoord.first, currentCoord.second - 1};
    pair<int, int> left = {currentCoord.first - 1, currentCoord.second};
    pair<int, int> right = {currentCoord.first + 1, currentCoord.second};

    // if the neighboring spaces are valid and are filled with air, push it to the adjacent vector
    if (up.first >= 0 && up.second >= 0 && up.first < size && up.second < size) {
        if (warehouse.at(up.first).at(up.second) == '.') {
            adjacent.push_back(up);
        }
    }
    if (down.first >= 0 && down.second >= 0 && down.first < size && down.second < size) {
        if (warehouse.at(down.first).at(down.second) == '.') {
            adjacent.push_back(down);
        }
    }
    if (left.first >= 0 && left.second >= 0 && left.first < size && left.second < size) {
        if (warehouse.at(left.first).at(left.second) == '.') {
            adjacent.push_back(left);
        }
    }
    if (right.first >= 0 && right.second >= 0 && right.first < size && right.second < size) {
        if (warehouse.at(right.first).at(right.second) == '.') {
            adjacent.push_back(right);
        }
    }

    for (auto& i : adjacent) {
        if (!visited[i]) {
            numSpacesFound += dfs(i, visited);
        }
    }
    return numSpacesFound;
}