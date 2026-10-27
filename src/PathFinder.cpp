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


using namespace std;

int PathFinder::calcH (const Point a, const Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void PathFinder::searchPath(Warehouse& w, Robot& r, Task& t) {

    vector<vector<char>> grid = w.getGrid();

    //Grid is AxA, so same cols and rows
    int rows = w.getSize();
    int cols = w.getSize();

    int xint = t.getPickupPosition().first;
    int yint = t.getPickupPosition().second;
    int xend = t.getDropoffPosition().first;
    int yend = t.getDropoffPosition().second;

    //Check that the initial positions are open
    if (grid[xint][yint] != '.' && grid[xend][yend] != '.') {
        cerr << "Path impossible!" << endl;
    }

    //Create a vector to reconstruct path to the parent
    vector<vector<pair<int, int>>> parentPath(rows, vector<pair<int, int>>(cols, {-1. -1}));

    //Closed Set: Tracks nodes we have already visited
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    //Create a vector to trak the lowest g-score
    vector<vector<int>> gScore(rows, vector<int>(cols, 0));

    //Create a priority queue based on the calculated weight
    priority_queue<Node, vector<Node> pq;

}