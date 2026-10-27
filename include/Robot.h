//
// Created by leafy on 10/20/2026.
//

#ifndef ROBOT_FLEET_ROBOT_H
#define ROBOT_FLEET_ROBOT_H
#include <vector>

using namespace std;

class Robot {
    public:
    Robot(string n, int b, pair<int, int> p, string s);

    string getName() const;

    ~Robot() = default;
    string getName() const;
    void setName(string n);
    int getBattery() const;
    void setBattery(int b);
    pair<int, int> getPositon();
    void setPositon(pair <int, int> p);
    string getStatus();
    void setStatus(string s);
    vector <pair <int, int>> getPath();
    void pushPath(pair <int, int> p);
    pair<int, int> popPath();

    private:
    vector <pair <int, int>> path;
    string name;
    int battery;
    pair<int,int> position;
    string status;

};


#endif //ROBOT_FLEET_ROBOT_H
