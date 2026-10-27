//
// Created by leafy on 10/20/2026.
//

#include <string>
#include <utility>

#include "../include/Robot.h"


Robot::Robot(const string n, const int b, const pair<int, int> p, string s)
    : name(n), battery(b), position(p), status(std::move(s))
{
}

string Robot::getName() const {
    return name;
}

void Robot::setName(string n) {
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

vector<pair <int, int>> Robot::getPath() {
    return path;
}