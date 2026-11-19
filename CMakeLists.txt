cmake_minimum_required(VERSION 4.3)
project(Robot_Fleet)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)
include_directories(src)

add_executable(Robot_Fleet
        include/Obstacle.h
        include/ObstacleManager.h
#        include/PathFinder.h
        include/Robot.h
        include/RobotManager.h
        include/System.h
        include/Task.h
        include/TaskManager.h
#        include/TempWarehouse.h
        include/Warehouse.h
        src/main.cpp
        src/Obstacle.cpp
        src/ObstacleManager.cpp
#        src/PathFinder.cpp
        src/Robot.cpp
        src/RobotManager.cpp
        src/System.cpp
        src/Task.cpp
        src/TaskManager.cpp
#        src/TempWarehouse.cpp
        src/Warehouse.cpp
        include/Point.h)
