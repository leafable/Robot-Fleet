#ifndef ROBOT_FLEET_ROBOT_H
#define ROBOT_FLEET_ROBOT_H
#include <stack>
#include <vector>
//#include "PathFinder.h"


class Task;
class Warehouse;
using namespace std;

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


class Robot {
public:
    Robot(char n, int b, pair<int, int> p, string s);
    ~Robot() = default;

    char getName() const;
    void setName(char n);
    int getBattery() const;
    void setBattery(int b);
    pair<int, int> getPositon();
    void setPositon(pair <int, int> p);
    string getStatus();
    void setStatus(string s);
    stack <pair <int, int>> getPath();
    void pushPath(vector<Point> p);
    void popPath();
    pair<int, int> peekPath();
    bool isPathEmpty();

    int calcH(Point a, Point b);

    vector<Point> searchPath(Warehouse &w, Task &t);

private:
    stack<pair <int, int>> path;
    char name;
    int battery;
    pair<int,int> position;
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
