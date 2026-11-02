//
// Created by admin on 10/25/26.
//

#include "PathFinder.h"
#include "Robot.h"
#include "Task.h"
#include "Warehouse.h"


#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <queue>


using namespace std;

int PathFinder::calcH (const Point a, const Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<Point> PathFinder::searchPath(Warehouse& w, Robot& r, Task& t) {

    vector<vector<char>> grid = w.getGrid();

    //Grid is AxA, so same cols and rows
    int rows = w.getSize();
    int cols = w.getSize();

    Point start = (t.getPickupPosition().first, t.getPickupPosition().second);
    Point goal = (t.getDropOffPosition().first, t.getDropOffPosition().second);

    int xint = t.getPickupPosition().first;
    int yint = t.getPickupPosition().second;
    int xend = t.getDropOffPosition().first;
    int yend = t.getDropoffPosition().second;

    //Check that the initial positions are open
    if (grid[yint][xint] != '.' && grid[yend][xend] != '.') {
        cerr << "Path impossible!" << endl;
    }

    //Create a vector to reconstruct path to the parent
    vector<vector<Point>> parentPath(rows, vector<Point>(cols, {-1, -1}));

    //Closed Set: Tracks nodes we have already visited
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    //Create a vector to track the lowest g-score
    vector<vector<int>> gScore(rows, vector<int>(cols, 0));

    //Open set: Create a priority queue based on the calculated weight
    std::priority_queue<Node, vector<Node>, greater<Node>> open;

    gScore[yint][xint] = 0;
    int hStart = calcH(start, goal);

    open.push(start, 0, hStart, hStart);

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

                        open.push({neigh, tempG, h, tempG + h});
                    }
                }
            }
        }
    }

    vector<Point> path;

    if (pathFound) {
        Point curr = goal;

        while (curr != goal) {
            path.push_back(curr);
            curr = {parentPath[curr.y][curr.x]};  //should x and y be flipped?
        }

        path.push_back(start);
        reverse(path.begin(), path.end());

    }

    return path;

}