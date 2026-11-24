#ifndef ROBOT_FLEET_TASKMANAGER_H
#define ROBOT_FLEET_TASKMANAGER_H
#include <vector>
#include <deque>
#include "Point.h"
#include "Task.h"

using namespace std;

class TaskManager {
private:
    deque<Task> taskQueue;
    vector<Task> activeTasks;
    vector<int> noTasksCounter;

public:
    TaskManager() = default;
    ~TaskManager() = default;
    void addTask(vector<Point> coords);
    void addTask(const Point &pickup, const Point &dropOff);
    Task popTask();
    bool containsTask(const Point& coord) const;
    int getSize() const;
    deque<Task> &getQueuedTasks();
    vector<Task> &getActiveTasks();
    vector<int> &getNoTasksCounter();
};


#endif //ROBOT_FLEET_TASKMANAGER_H
