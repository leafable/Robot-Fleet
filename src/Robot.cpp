#include "Robot.h"
//
// Created by leafy on 10/20/2026.
//

#include <string>
#include <utility>

#include "Robot.h"

#include <iostream>

#include "Task.h"
#include "Warehouse.h"


Robot::Robot(const char c, const int b, const std::pair<int, int> p, std::string s)
    : name(c), battery(b), position(p), status(std::move(s))
{
}

char Robot::getName() const {
    return name;
}

void Robot::setName(char n) {
    name = std::move(n);
}

int Robot::getBattery() const {
    return battery;
}

void Robot::setBattery(const int b) {
    battery = b;
}

pair<int, int> Robot::getPositon() {
    return position;
}

void Robot::setPositon(pair <int, int> p) {
    position = p;
}

string Robot::getStatus() {
    return status;
}

void Robot::setStatus(string s) {
    status = s;
}

stack<pair <int, int>> Robot::getPath() {
    return path;
}

void Robot::pushPath(vector <Point> p) {
    for (int i = 0; i < p.size(); i++) {
        pair <int, int> pt = {p[i].x, p[i].y};
        path.push(pt);
    }


}


void Robot::popPath() {
    path.pop();
}

pair<int,int> Robot::peekPath() {
    return path.top();
}

bool Robot::isPathEmpty() {
    return path.empty();
}

int Robot::calcH (const Point a, const Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<Point> Robot::searchPath(TempWarehouse& w, Task& t) {
    const vector<vector<char>> grid = {
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.'}, // 01
    {'.', '.', '.', 'o', 'o', 'o', 'o', 'o', '.', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.'}, // 02
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}, // 03
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', 'o', '.', 'o', '.', 'o'}, // 04
    {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', 'o', '.', 'o', '.', 'o'}, // 05
    {'o', 'o', 'o', 'o', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o'}, // 06
    {'o', 'o', 'o', 'o', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o'}, // 07
    {'.', '.', '.', '.', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o'}, // 08
    {'.', '.', 'o', '.', 'o', '.', 'o', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 09
    {'.', '.', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 10
    {'.', '.', 'o', '.', 'o', 'o', '.', '.', '.', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '.', '.', '.'}, // 11
    {'.', '.', 'o', '.', 'o', 'o', '.', 'o', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 12
    {'.', '.', '.', '.', 'o', 'o', '.', 'o', '.', '.', '.', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 13
    {'.', '.', '.', '.', 'o', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}, // 14
    {'.', '.', '.', '.', 'o', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.'}, // 15
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.'}, // 16
    {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', 'o', '.', '.', '.', '.'}, // 17
    {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o', 'o'}, // 18
    {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o'}, // 19
    {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.'}  // 20
    };


    //Grid is AxA, so same cols and rows
    int rows = 20;
    int cols = 20;

    Point start = {t.getPickupPosition().first, t.getPickupPosition().second};
    Point goal = {t.getDropOffPosition().first, t.getDropOffPosition().second};

    int xint = t.getPickupPosition().first;
    int yint = t.getPickupPosition().second;
    int xend = t.getDropOffPosition().first;
    int yend = t.getDropOffPosition().second;

    //Check that the initial positions are open
    if ((grid[yint][xint] != '.') && (grid[yend][xend] != '.')) {
        cerr << "Path impossible!" << endl;
    }

    //Create a vector to reconstruct path to the parent
    vector<vector<Point>> parentPath(rows, vector<Point>(cols, {-1, -1}));

    //Closed Set: Tracks nodes we have already visited
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    //Create a vector to track the lowest g-score
    //Should this be int max or 0
    vector<vector<int>> gScore(rows, vector<int>(cols, INT_MAX));

    //Open set: Create a priority queue based on the calculated weight
    std::priority_queue<Node, vector<Node>, greater<Node>> open;

    gScore[yint][xint] = 0;
    int hStart = calcH(start, goal);

    Node n = Node(start, 0, hStart, hStart);

    open.push(n);

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    bool pathFound = false;

    while (!open.empty()){
        Node current = open.top();
        open.pop();

        if (current.point == goal) {
            pathFound = true;
            break;
        }

        if (current.g > gScore[current.point.y][current.point.x]) {
            continue;
        }

        for (int i = 0; i < 4; i++) {
            Point neigh = {current.point.x + dx[i], current.point.y + dy[i]};

            if (neigh.y >= 0 && neigh.y < rows && neigh.x >= 0 && neigh.x < cols) {
                if (grid[neigh.y][neigh.x] == '.') {
                    int tempG = current.g + 1;

                    if (tempG < gScore[neigh.y][neigh.x]) {
                        gScore[neigh.y][neigh.x] = tempG;
                        parentPath[neigh.y][neigh.x] = current.point;

                        int h = calcH(neigh, goal);

                        open.emplace(neigh, tempG, h, tempG + h);


                    }
                }
            }
        }
    }

    vector<Point> path;

    if (pathFound) {
        Point curr = goal;

        while (curr != start) {
            path.push_back(curr);
            curr = parentPath[curr.y][curr.x];  //should x and y be flipped?
        }

        path.push_back(start);
        reverse(path.begin(), path.end());

    }

    return path;

}