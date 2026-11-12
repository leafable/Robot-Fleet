//
// Created by leafy on 11/11/2026.
//

#ifndef POINT_H
#define POINT_H


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

    bool operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }

    //private:
    int x;
    int y;
};


#endif //POINT_H
