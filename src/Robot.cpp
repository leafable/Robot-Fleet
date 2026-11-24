#include <utility>
#include <algorithm>
#include <queue>
#include <iostream>
#include "Robot.h"
#include "Task.h"
#include "Warehouse.h"

Robot::Robot(const char n, const int b, const Point &p, string s)
    : name(n), battery(b), position(p), status(std::move(s)), carry(false)
{
}

char Robot::getName() const {
    return name;
}

void Robot::setName(const char n) {
    name = n;
}

int Robot::getBattery() const {
    return battery;
}

void Robot::setBattery(const int b) {
    battery = b;
}

Point Robot::getPosition() const {
    return position;
}

void Robot::setPosition(const Point &p) {
    if (p.x >= 0 && p.y >= 0)
        position = p;
}

string Robot::getStatus() const {
    return status;
}

void Robot::setStatus(const string &s) {
    status = s;
}

stack<Point> Robot::getPath() {
    if (!path.empty()) {
        return path;
    }
    return stack<Point>({{-1, -1}});
}

// void Robot::pushPath(vector <Point> p) {
//     for (int i = 0; i < p.size(); i++) {
//         Point pt = {p[i].x, p[i].y};
//         path.push(pt);
//     }
// }

void Robot::popPath() {
    if (!path.empty()) {
        path.pop();
    }
}

Point Robot::peekPath() {
    if (!path.empty()) {
        return path.top();
    }
    return {-1, -1};
}

bool Robot::isPathEmpty() const {
    return path.empty();
}

int Robot::calcH (const Point a, const Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void Robot::searchPath(const Warehouse& w, const Point &pickup, const Point &dropoff) {
    // const vector<vector<char>> grid = {
    // {'.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.'}, // 01
    // {'.', '.', '.', 'o', 'o', 'o', 'o', 'o', '.', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.'}, // 02
    // {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}, // 03
    // {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', 'o', '.', 'o', '.', 'o'}, // 04
    // {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', 'o', '.', 'o', '.', 'o'}, // 05
    // {'o', 'o', 'o', 'o', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o'}, // 06
    // {'o', 'o', 'o', 'o', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o'}, // 07
    // {'.', '.', '.', '.', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o'}, // 08
    // {'.', '.', 'o', '.', 'o', '.', 'o', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 09
    // {'.', '.', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 10
    // {'.', '.', 'o', '.', 'o', 'o', '.', '.', '.', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', '.', '.', '.'}, // 11
    // {'.', '.', 'o', '.', 'o', 'o', '.', 'o', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 12
    // {'.', '.', '.', '.', 'o', 'o', '.', 'o', '.', '.', '.', 'o', 'o', '.', '.', '.', '.', '.', '.', '.'}, // 13
    // {'.', '.', '.', '.', 'o', 'o', '.', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}, // 14
    // {'.', '.', '.', '.', 'o', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.'}, // 15
    // {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.'}, // 16
    // {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', 'o', '.', '.', '.', '.'}, // 17
    // {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '.', 'o', 'o', 'o'}, // 18
    // {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o'}, // 19
    // {'o', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.', '.', 'o', 'o', 'o', 'o', '.', '.', '.', '.', '.'}  // 20
    // };

    const vector<vector<char>> grid = *w.getWarehouse();

    //Grid is AxA, so same cols and rows
    int rows = w.getWarehouseSize();
    int cols = w.getWarehouseSize();

    Point start = {pickup.x, pickup.y};
    Point goal = {dropoff.x, dropoff.y};

    int xint = pickup.x;
    int yint = pickup.y;
    int xend = dropoff.x;
    int yend = dropoff.y;

    //Check that the initial positions are open
    if ((grid[yint][xint] == '#') || (grid[yend][xend] == '#')) {
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
    priority_queue<Node, vector<Node>, greater<Node>> open;

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

            if (neigh.x >= 0 && neigh.x < rows && neigh.y >= 0 && neigh.y < cols) {
                if (grid[neigh.y][neigh.x] != '#') {
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

    // vector<Point> path;

    if (pathFound) {
        Point curr = goal;

        while (curr != start) {
            path.push(curr);
            curr = parentPath[curr.y][curr.x];  //should x and y be flipped?
        }

        // path.push(start);
        // reverse(path.begin(), path.end());

    }

    // return path;
}

void Robot::moveRobot(Task &task) {
    //When the robot has no charge the status is set to charging
    if (getBattery() == 0) {
        setStatus("Charging");
    }

    //When the charging status is set, it will only change when the robot
    //is at full charge (5 moves)
    if (getStatus() == "Charging" && getBattery() < 100) {
        setBattery(getBattery() + 20);
        return;
    }

    //Once the robot is charged to 100, it will check and set the status for continuing moves
    if (getStatus() == "Charging" && getBattery() == 100) {
        setStatus(isPathEmpty() ? "Idle" : "Active");
    }

    if (isPathEmpty()) {
        setStatus("Idle");
        task.setDropOffStatus(true);
        carry = false;
        return;
    }

    //This is where the robot is between 100 and 0, but not charging,
    //they will simply process one move
    setPosition(peekPath());
    path.pop();
    setBattery(getBattery() - 5);
    if (position == task.getPickupPosition()) {
        task.setPickupStatus(true);
        carry = true;
    }
    setStatus(isPathEmpty() ? "Idle" : "Active");
    if (isPathEmpty()) {
        task.setDropOffStatus(true);
        carry = false;
    }
}

bool Robot::isCarrying() const {
    return carry;
}