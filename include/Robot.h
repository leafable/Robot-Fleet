#ifndef ROBOT_FLEET_ROBOT_H
#define ROBOT_FLEET_ROBOT_H
#include <stack>
#include <vector>
#include <string>
#include "Warehouse.h"
#include "Point.h"

class Task;
class Warehouse;
using namespace std;

class Robot {
public:
    Robot(int n, int b, const Point &p, string s);
    ~Robot() = default;

    int getName() const;
    void setName(int n);
    int getBattery() const;
    void setBattery(int b);
    Point getPosition() const;
    void setPosition(const Point &p);
    string getStatus() const;
    void setStatus(const string &s);
    stack<Point> getPath();
    void pushPath(vector<Point> p);
    void popPath();
    Point peekPath();
    bool isPathEmpty() const;
    int calcH(Point a, Point b);
    vector<Point> searchPath(Warehouse &w, Task &t);
    vector<Point> searchPath(const Warehouse &w, const Point &pickup, const Point &dropoff);
    void moveRobot();
    Point nextMove();

private:
    stack<Point> path;
    int name;
    int battery;
    Point position;
    string status;

    struct Node {
        Point point;
        int f, g, h;
        //Node* parent;

        //Node(Point p, int g, int h, int f, Node* n) : point(p), g(g), h(h), f(f), parent(n) {}

        Node(Point p, int g, int h, int f) : point(p), f(f), g(g), h(h) {}

        //Custom operator to quickly compare f values
        bool operator()(const Node* a, const Node* b) const {
            return a->f > b->f;
        }

        // Overload < operator for max-heap (higher priority comes first)
        bool operator>(const Node& other) const {
            return this->f > other.f;
        }
    };

};


#endif //ROBOT_FLEET_ROBOT_H