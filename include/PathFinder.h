//
// Created by admin on 10/25/26.
//

#ifndef ROBOT_FLEET_PATHFINDER_H
#define ROBOT_FLEET_PATHFINDER_H

class Task;
class Robot;
class Warehouse;

//Create a struct to implement A* search
struct Point {

    Point() : x(-1), y(-1) {}
    Point(const int x, const int y) : x(x), y(y) {}

    //Custom equality operator checking coordinates
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    //Custom inequality operator
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    //private:
    int x;
    int y;
};

class PathFinder {
    public:
    PathFinder();
    ~PathFinder();
    static int calcH (Point a, Point b);
    void searchPath(Warehouse& w, Robot& r, Task& t);

    private:
        // Creates a private struct to hold data of visited nodes
        struct Node {
            Point point;
            int f, g, h;
            Node* parent;

            //Custom operator to quickly compare f values
            bool operator()(const Node* a, const Node* b) const {
                return a->f > b->f;
            }
        };

};


#endif //ROBOT_FLEET_PATHFINDER_H
