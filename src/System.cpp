#include "System.h"

int System::randomSeed = random_device{}();
int System::numRobots = 3;
int System::numTasks = 3;

System::System() : seed(randomSeed), warehouse(20), obstacles(warehouse.getWarehouseSize(), warehouse, seed), robots(warehouse, seed, numRobots), tasks('A', warehouse, seed, numTasks) {
}

System::~System() = default;

void System::printWarehouse() {
    cout << warehouse.getWarehouseStr();
}

void System::runProcess() {

    int selection_main{};
    int numSteps = 1;
    string statusStr;
    string tasksStr;

    do {
        int selection_tasks{};

        int selection_config{};
        int temp_numSteps{};
        int temp_numObstacles{};
        int temp_warehouseSize{};
        int temp_numRobots{};
        int temp_randomSeed{};
        Point temp_pickupCoord{};
        Point temp_dropoffCoord{};

        activeTasks.resize(robots.getNumRobots());
        noTasksCounter.resize(robots.getNumRobots());
        warehouse.drawRobots(robots.getRobots());
        warehouse.drawTasks(tasks.getTasks(), activeTasks);

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
        for (int i = 0; auto& it : noTasksCounter) {
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

        // Main menu logic
        if (selection_main == 1) {
            // Advance simulation
            for (int i = 0; auto& robot : robots.getRobots()) {
                for (int j = 0; j < numSteps; j++) {
                    if (robot.getStatus() == "Idle" && tasks.getSize()) {
                        noTasksCounter[i] = {};
                        activeTasks[i] = Task(tasks.popTask());
                        robot.searchPath(warehouse, activeTasks[i].getPickupPosition(), activeTasks[i].getDropoffPosition());
                        robot.searchPath(warehouse, robot.getPosition(), activeTasks[i].getPickupPosition());
                    }
                    else if (robot.getStatus() == "Idle" && !tasks.getSize()) {
                        activeTasks[i] = {};
                        noTasksCounter[i]++;
                    }
                    warehouse.updateRobot(robot, activeTasks[i]);
                    warehouse.updateTask(robot, activeTasks[i]);
                }
                i++;
            }
        }
        else if (selection_main == 2) {
            // Print the status of each robot
            stringstream ss;
            for (int i = 0; const auto& robot : robots.getRobots()) {
                ss << "Robot " << robot.getName() - 48 << " | ";
                ss << "Status: " << setw(8) << right << robot.getStatus() << " | ";
                ss << "Battery: " << setw(3) << right << robot.getBattery() << "% | ";
                if (activeTasks[i].getPickupName() != ' ' && activeTasks[i].getDropoffName() != ' ') {
                    ss << "Task: " << activeTasks[i].getPickupName() << " -> " << activeTasks[i].getDropoffName() << " | ";
                    ss << "Carrying: " << setw(3) << right << (robot.isCarrying() ? "Yes" : "No") << " | ";
                    ss << "Progress: Moving towards " << (robot.isCarrying() ? activeTasks[i].getDropoffName() : activeTasks[i].getPickupName());
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

            ss << "Active tasks:";
            bool containsActiveTasks{};
            for (const auto& task : activeTasks) {
                if (task.getPickupName() != ' ' && task.getDropoffName() != ' ') {
                    ss << endl << task.getPickupName() << "(" << setfill('0') << setprecision(2) << task.getPickupPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getPickupPosition().y + 1 << ") -> " <<
                        task.getDropoffName() << "(" << setfill('0') << setprecision(2) << setw(2) << right << task.getDropoffPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getDropoffPosition().y + 1 << ")";
                    containsActiveTasks = true;
                }
            }

            // If no points are displayed, print N/A
            if (!containsActiveTasks) {
                ss << " N/A";
            }

            ss << endl << endl << "Queued tasks:";
            bool containsQueuedTasks{};
            for (const auto& task : tasks.getTasks()) {
                ss << endl << task.getPickupName() << "(" << setfill('0') << setprecision(2) << setw(2) << right << task.getPickupPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getPickupPosition().y + 1 << ") -> " <<
                    task.getDropoffName() << "(" << setfill('0') << setprecision(2) << setw(2) << right << task.getDropoffPosition().x + 1 << ", " << setfill('0') << setprecision(2) << setw(2) << right << task.getDropoffPosition().y + 1 << ")";
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
            // Roll for a valid pickupCoord
            Point pickupCoord;
            do {
                uniform_int_distribution<int> pickupX(0, warehouse.getWarehouseSize() - 1);
                uniform_int_distribution<int> pickupY(0, warehouse.getWarehouseSize() - 1);
                pickupCoord = {pickupX(seed), pickupY(seed)};
            } while (!warehouse.isAir(pickupCoord));

            // Roll for a valid dropoffCoord
            Point dropoffCoord;
            do {
                uniform_int_distribution<int> dropoffX(0, warehouse.getWarehouseSize() - 1);
                uniform_int_distribution<int> dropoffY(0, warehouse.getWarehouseSize() - 1);
                dropoffCoord = {dropoffX(seed), dropoffY(seed)};
            } while (!warehouse.isAir(dropoffCoord));

            tasks.addTask(Task(tasks.getSize() ? tasks.getTasks().back().getDropoffName() + 1 : 'A', pickupCoord, dropoffCoord));
        }
        else if (selection_tasks == 2) {
            // Ask the user for a valid pickup location
            do {
                temp_pickupCoord.x = getSelection(1, warehouse.getWarehouseSize(), "Pickup X: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_pickupCoord.y = getSelection(1, warehouse.getWarehouseSize(), "Pickup Y: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_pickupCoord.x--;
                temp_pickupCoord.y--;
                if (!warehouse.isAir(temp_pickupCoord)) {
                    cout << "Error: Coordinate is occupied!" << endl;
                }
            } while (!warehouse.isAir(temp_pickupCoord));

            // Ask the user for a valid dropoff location
            do {
                temp_dropoffCoord.x = getSelection(1, warehouse.getWarehouseSize(), "Dropoff X: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_dropoffCoord.y = getSelection(1, warehouse.getWarehouseSize(), "Dropoff Y: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_dropoffCoord.x--;
                temp_dropoffCoord.y--;
                if (!warehouse.isAir(temp_pickupCoord)) {
                    cout << "Error: Coordinate is occupied!" << endl;
                }
            } while (!warehouse.isAir(temp_dropoffCoord));

            // Push the new task onto the vector of tasks
            tasks.addTask(Task(tasks.getSize() ? tasks.getTasks().back().getDropoffName() + 1 : 'A', temp_pickupCoord, temp_dropoffCoord));
        }


        // Logic for config sub menu
        if (selection_config == 1) {
            // Change simulation step count
            cout << "Current increment interval: " << numSteps << endl;
            temp_numSteps = getSelection(1, 10, "Steps: ", "Error: Invalid step count (1-10)");
            numSteps = temp_numSteps;
        }
        else if (selection_config == 2) {
            // Change number of obstacles
            cout << "Current number of obstacles: " << obstacles.getNumObstacles() << endl;
            temp_numObstacles = getSelection(0, numeric_limits<int>::max() - 1, "Number of obstacles: ", "Error: Invalid number of obstacles (0+)");
            seed.seed(randomSeed);
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(temp_numObstacles, warehouse, seed);
            robots = RobotManager(warehouse, seed, robots.getNumRobots());
            tasks = TaskManager('A', warehouse, seed, numTasks);
            activeTasks.clear();
            noTasksCounter.clear();
        }
        else if (selection_config == 3) {
            // Change number of robots
            cout << "Current number of robots: " << robots.getNumRobots() << endl;
            temp_numRobots = getSelection(1, 9, "Number of robots: ", "Error: Invalid number of robots (1-9)");
            if (temp_numRobots > robots.getNumRobots()) {
                // Reset the random number generator
                seed.seed(randomSeed);
                // Discard the first few random numbers so that robots generate in the correct place
                seed.discard(temp_numRobots - robots.getNumRobots());
                robots.addRobot(warehouse, seed, temp_numRobots - robots.getNumRobots());
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
            temp_warehouseSize = getSelection(5, 50, "Warehouse size: ", "Error: Invalid warehouse size (5+)");
            seed.seed(randomSeed);
            warehouse = Warehouse(temp_warehouseSize);
            // The arbitrary number of obstacles for the new warehouse should be the size of the warehouse
            obstacles = ObstacleManager(temp_warehouseSize, warehouse, seed);
            robots = RobotManager(warehouse, seed, robots.getNumRobots());
            tasks = TaskManager('A', warehouse, seed, numTasks);
            activeTasks.clear();
            noTasksCounter.clear();
        }
        else if (selection_config == 5) {
            // Set warehouse seed
            cout << "Current seed: " << randomSeed << endl;
            temp_randomSeed = getSelection(numeric_limits<int>::min() + 1, numeric_limits<int>::max() - 1, "Set seed: ", "Error: Invalid seed (0+)");
            randomSeed = temp_randomSeed;
            seed.seed(randomSeed);
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, seed);
            robots = RobotManager(warehouse, seed, robots.getNumRobots());
            tasks = TaskManager('A', warehouse, seed, numTasks);
            activeTasks.clear();
            noTasksCounter.clear();
        }
        else if (selection_config == 6) {
            // Reset warehouse
            seed.seed(randomSeed);
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, seed);
            robots = RobotManager(warehouse, seed, robots.getNumRobots());
            tasks = TaskManager('A', warehouse, seed, numTasks);
            activeTasks.clear();
            noTasksCounter.clear();
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