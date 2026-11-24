#include "System.h"

int System::randomSeed = static_cast<int>(random_device{}());

System::System() : seed(randomSeed), warehouse(defaultWarehouseSize), obstacles(warehouse.getWarehouseSize(), warehouse, seed) {
    robots.addRobot(generateValidCoords(defaultNumRobots));
    tasks.addTask(generateValidCoords(defaultNumTasks * 2));
}

System::~System() = default;

void System::printWarehouse() {
    cout << warehouse.getWarehouseStr(robots.getRobots(), tasks.getQueuedTasks(), tasks.getActiveTasks());
}

vector<Point> System::generateValidCoords(const int numCoords) {
    if (numCoords <= 0) {
        return {{-1, -1}};
    }

    vector<Point> coords;
    do {
        uniform_int_distribution<int> coordX(0, warehouse.getWarehouseSize() - 1);
        uniform_int_distribution<int> coordY(0, warehouse.getWarehouseSize() - 1);
        Point coord = {coordX(seed), coordY(seed)};

        if (isValidCoord(coord)) {
            coords.push_back(coord);
        }
    } while (coords.size() != numCoords);

    return coords;
}

bool System::isValidCoord(const Point& coord) const {
    return !warehouse.containsObstacle(coord) && !robots.containsRobot(coord) && !tasks.containsTask(coord);
}

void System::runProcess() {

    int selection_main{};
    int numSteps = 1;
    string statusStr;
    string tasksStr;

    do {
        tasks.getActiveTasks().resize(robots.getNumRobots());
        tasks.getNoTasksCounter().resize(robots.getNumRobots());

        printWarehouse();

        if (!statusStr.empty()) {
            cout << endl << statusStr;
            statusStr.clear();
        }

        if (!tasksStr.empty()) {
            cout << endl << tasksStr << endl;
            tasksStr.clear();
        }

        bool printed{};
        for (int i = 0; auto& it : tasks.getNoTasksCounter()) {
            if (it) {
                cout << endl << "Robot " << i + 1 << ": No existing tasks! [x" << it << "]";
                printed = true;
            }
            i++;
        }

        // Extra padding
        if (printed) {
            cout << endl;
        }

        cout << endl;
        cout << "1). Advance simulation " << numSteps << " step" << endl;
        cout << "2). Display robot/task status" << endl;
        cout << "3). View all tasks" << endl;
        cout << "4). Create a new task" << endl;
        cout << "5). Configuration" << endl;
        cout << "6). Exit" << endl;

        selection_main = getSelection(1, 6);

        int selection_tasks{};
        int selection_config{};

        // Main menu logic
        if (selection_main == 1) {
            // Advance simulation
            for (int robotIndex = 0; auto& robot : robots.getRobots()) {
                for (int step = 0; step < numSteps; step++) {
                    if (robot.getStatus() == "Idle" && tasks.getSize()) {
                        tasks.getActiveTasks()[robotIndex] = tasks.popTask();
                        tasks.getActiveTasks()[robotIndex].setAssigned(true);
                        tasks.getNoTasksCounter()[robotIndex] = {};
                        robot.searchPath(warehouse, tasks.getActiveTasks()[robotIndex].getPickupPosition(), tasks.getActiveTasks()[robotIndex].getDropOffPosition());
                        robot.searchPath(warehouse, robot.getPosition(), tasks.getActiveTasks()[robotIndex].getPickupPosition());
                    }
                    else if (robot.getStatus() == "Idle" && !tasks.getSize()) {
                        tasks.getActiveTasks()[robotIndex] = {};
                        tasks.getNoTasksCounter()[robotIndex]++;
                    }
                    robot.moveRobot(tasks.getActiveTasks()[robotIndex]);
                }
                robotIndex++;
            }
        }
        else if (selection_main == 2) {
            // Print the status of each robot
            stringstream ss;
            for (int i = 0; const auto& robot : robots.getRobots()) {
                ss << "Robot " << robot.getName() - 48 << " | ";
                ss << "Status: " << setw(8) << right << robot.getStatus() << " | ";
                ss << "Battery: " << setw(3) << right << robot.getBattery() << "% | ";
                if (tasks.getActiveTasks()[i].isAssigned()) {
                    ss << "Task: " << tasks.getActiveTasks()[i].getPickupName() << " -> " << tasks.getActiveTasks()[i].getDropOffName() << " | ";
                    ss << "Carrying: " << setw(3) << right << (robot.isCarrying() ? "Yes" : "No") << " | ";
                    ss << "Progress: Moving towards " << (robot.isCarrying() ? tasks.getActiveTasks()[i].getDropOffName() : tasks.getActiveTasks()[i].getPickupName());
                }
                else {
                    ss << "Task: " << setw(6) << right << "None" << " | ";
                    ss << "Carrying: " << setw(3) << right << "No" << " | ";
                    ss << "Progress: N/A";
                }
                ss << endl;
                i++;
            }
            statusStr = ss.str();
        }
        else if (selection_main == 3) {
            // View all tasks
            stringstream ss;

            bool containsActiveTasks{};
            ss << "Active tasks:";
            for (const auto& task : tasks.getActiveTasks()) {
                if (task.isAssigned()) {
                    ss << endl << task.getPickupName() << "(" << setfill('0') << setprecision(2) << task.getPickupPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getPickupPosition().y + 1 << ") -> " <<
                        task.getDropOffName() << "(" << setfill('0') << setprecision(2) << setw(2) << right << task.getDropOffPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getDropOffPosition().y + 1 << ")";
                    containsActiveTasks = true;

                }
            }

            // If no points are displayed, print N/A
            if (!containsActiveTasks) {
                ss << " N/A";
            }

            bool containsQueuedTasks{};
            ss << endl << endl << "Queued tasks:";
            for (const auto& task : tasks.getQueuedTasks()) {
                ss << endl << task.getPickupName() << "(" << setfill('0') << setprecision(2) << setw(2) << right << task.getPickupPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getPickupPosition().y + 1 << ") -> " <<
                    task.getDropOffName() << "(" << setfill('0') << setprecision(2) << setw(2) << right << task.getDropOffPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getDropOffPosition().y + 1 << ")";
                containsQueuedTasks = true;
            }

            // If no points are displayed, print N/A
            if (!containsQueuedTasks) {
                ss << " N/A";
            }

            tasksStr = ss.str();
        }
        else if (selection_main == 4) {
            // Assign a task to a robot
            cout << "1). Randomize task pickup/dropoff locations" << endl;
            cout << "2). Manually input pickup/dropoff locations" << endl;
            cout << "3). Main menu" << endl;
            selection_tasks = getSelection(1, 3);
        }
        else if (selection_main == 5) {
            // Configuration (sub menu)
            cout << "1). Change simulation step count" << endl;
            cout << "2). Change number of obstacles" << endl;
            cout << "3). Change number of robots" << endl;
            cout << "4). Change warehouse size" << endl;
            cout << "5). Set warehouse seed" << endl;
            cout << "6). Reset warehouse" << endl;
            cout << "7). Main menu" << endl;
            selection_config = getSelection(1, 7);
        }
        else if (selection_main == 6) {
            // Exit
            cout << "Exiting..." << endl;
        }


        // Logic for tasks sub menu
        if (selection_tasks == 1) {
            tasks.addTask(generateValidCoords(2));
        }
        else if (selection_tasks == 2) {
            // Ask the user for a valid pickup location
            Point temp_pickupCoord{};
            do {
                temp_pickupCoord.x = getSelection(1, warehouse.getWarehouseSize(), "Pickup X: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_pickupCoord.y = getSelection(1, warehouse.getWarehouseSize(), "Pickup Y: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_pickupCoord.x--;
                temp_pickupCoord.y--;
                if (!isValidCoord(temp_pickupCoord)) {
                    cout << "Error: Coordinate is occupied!" << endl;
                }
            } while (!isValidCoord(temp_pickupCoord));

            // Ask the user for a valid dropoff location
            Point temp_dropOffCoord{};
            do {
                temp_dropOffCoord.x = getSelection(1, warehouse.getWarehouseSize(), "DropOff X: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_dropOffCoord.y = getSelection(1, warehouse.getWarehouseSize(), "DropOff Y: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_dropOffCoord.x--;
                temp_dropOffCoord.y--;
                if (!isValidCoord(temp_dropOffCoord)) {
                    cout << "Error: Coordinate is occupied!" << endl;
                }
            } while (!isValidCoord(temp_dropOffCoord) || temp_dropOffCoord == temp_pickupCoord);

            // Push the new task onto the vector of tasks
            tasks.addTask(temp_pickupCoord, temp_dropOffCoord);
        }


        // Logic for config sub menu
        if (selection_config == 1) {
            // Change simulation step count
            cout << "Current increment interval: " << numSteps << endl;
            int temp_numSteps = getSelection(1, 10, "Steps: ", "Error: Invalid step count (1-10)");
            numSteps = temp_numSteps;
        }
        else if (selection_config == 2) {
            // Change number of obstacles
            cout << "Current number of obstacles: " << obstacles.getNumObstacles() << endl;
            int temp_numObstacles = getSelection(0, numeric_limits<int>::max() - 1, "Number of obstacles: ", "Error: Invalid number of obstacles (0+)");
            seed.seed(randomSeed);
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(temp_numObstacles, warehouse, seed);
            int temp_numRobots = robots.getNumRobots();
            robots = RobotManager();
            robots.addRobot(generateValidCoords(temp_numRobots));
            tasks = TaskManager();
            tasks.addTask(generateValidCoords(defaultNumTasks * 2));
            tasks.getActiveTasks().clear();
            tasks.getNoTasksCounter().clear();
        }
        else if (selection_config == 3) {
            // Change number of robots
            cout << "Current number of robots: " << robots.getNumRobots() << endl;
            int temp_numRobots = getSelection(1, 9, "Number of robots: ", "Error: Invalid number of robots (1-9)");
            if (temp_numRobots > robots.getNumRobots()) {
                // Reset the random number generator
                seed.seed(randomSeed);
                // Discard the first few random numbers so that robots generate in the correct place
                seed.discard(temp_numRobots - robots.getNumRobots());
                robots.addRobot(generateValidCoords(temp_numRobots - robots.getNumRobots()));
            }
            else if (robots.getNumRobots() > temp_numRobots) {
                seed.seed(randomSeed);
                seed.discard(robots.getNumRobots() - temp_numRobots);
                robots.removeRobot(robots.getNumRobots() - temp_numRobots);
            }
        }
        else if (selection_config == 4) {
            // Change warehouse size
            cout << "Current warehouse size: " << warehouse.getWarehouseSize() << endl;
            int temp_warehouseSize = getSelection(5, 35, "Warehouse size: ", "Error: Invalid warehouse size (5+)");
            seed.seed(randomSeed);
            warehouse = Warehouse(temp_warehouseSize);
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, seed);
            int temp_numRobots = robots.getNumRobots();
            robots = RobotManager();
            robots.addRobot(generateValidCoords(temp_numRobots));
            tasks = TaskManager();
            tasks.addTask(generateValidCoords(defaultNumTasks * 2));
            tasks.getActiveTasks().clear();
            tasks.getNoTasksCounter().clear();
        }
        else if (selection_config == 5) {
            // Set warehouse seed
            cout << "Current seed: " << randomSeed << endl;
            int temp_randomSeed = getSelection(numeric_limits<int>::min() + 1, numeric_limits<int>::max() - 1, "Set seed: ", "Error: Invalid seed (0+)");
            randomSeed = temp_randomSeed;
            seed.seed(randomSeed);
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, seed);
            int temp_numRobots = robots.getNumRobots();
            robots = RobotManager();
            robots.addRobot(generateValidCoords(temp_numRobots));
            tasks = TaskManager();
            tasks.addTask(generateValidCoords(defaultNumTasks * 2));
            tasks.getActiveTasks().clear();
            tasks.getNoTasksCounter().clear();
        }
        else if (selection_config == 6) {
            // Reset warehouse
            seed.seed(randomSeed);
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, seed);
            int temp_numRobots = robots.getNumRobots();
            robots = RobotManager();
            robots.addRobot(generateValidCoords(temp_numRobots));
            tasks = TaskManager();
            tasks.addTask(generateValidCoords(defaultNumTasks * 2));
            tasks.getActiveTasks().clear();
            tasks.getNoTasksCounter().clear();
        }

    } while (selection_main != 6);
}

int System::getSelection(const int min, const int max) {
    return getSelection(min, max, "Enter selection: ", "Error: Invalid input: ");
}

int System::getSelection(const int min, const int max, const string& text, const string& error) {
    int selection{};
    bool flag{};

    do {
        if (!cin || flag) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << error << endl;
        }
        cout << text;

        flag = !(cin >> selection) || selection < min || selection > max;

        // // If bounded, then selection must be between start and end
        // if (bounded) {
        //     flag = !(cin >> selection) || selection < min || selection > max;
        // }
        // // If unbounded, then either selection must be greater than start, or less than end
        // else {
        //     // If both min and max == 0, arbitrarily assume selection must be positive
        //     if (min == 0 && max == 0) {
        //         flag = !(cin >> selection) || selection < min;
        //     }
        //     // If start == 0, then selection must be less than end
        //     else if (min == 0) {
        //         flag = !(cin >> selection) || selection > max;
        //     }
        //     // If end == 0, then selection must be greater than start
        //     else if (max == 0) {
        //         flag = !(cin >> selection) || selection < min;
        //     }
        //     // Debugging
        //     else {
        //         cerr << "Error: Invalid selection code" << endl;
        //     }
        // }
    } while (flag);

    return selection;
}