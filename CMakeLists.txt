cmake_minimum_required(VERSION 4.3)
project(Robot_Fleet)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Robot_Fleet
        src/Warehouse.cpp
        include/Warehouse.h
        src/main.cpp
        src/System.cpp
        include/System.h
        src/Obstacle.cpp
        include/Obstacle.h
#        src/Task.cpp
#        include/Task.h
        src/TaskManager.cpp
        include/TaskManager.h
        src/ObstacleManager.cpp
        include/ObstacleManager.h
        src/Robot.cpp
        include/Robot.h
        src/RobotManager.cpp
        include/RobotManager.h
        src/TempWarehouse.cpp
        include/TempWarehouse.h)
