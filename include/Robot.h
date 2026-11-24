#ifndef ROBOT_FLEET_ROBOT_H
#define ROBOT_FLEET_ROBOT_H
#include <stack>
#include <string>
#include "Point.h"
#include "Task.h"

class Warehouse;

using namespace std;

class Robot {
public:
    Robot(char n, int b, const Point &p, string s);
    ~Robot() = default;

    char getName() const;
    void setName(char n);
    int getBattery() const;
    void setBattery(int b);
    Point getPosition() const;
    void setPosition(const Point &p);
    string getStatus() const;
    void setStatus(const string &s);
    stack<Point> getPath();
    void searchPath(const Warehouse &w, const Point &pickup, const Point &dropoff);
    void moveRobot(Task &task);
    bool isCarrying() const;

private:
    stack<Point> path;
    char name;
    int battery;
    Point position;
    string status;
    bool carry;

    int calcH(Point a, Point b);
    // void pushPath(vector<Point> p);
    void popPath();
    Point peekPath();
    bool isPathEmpty() const;


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