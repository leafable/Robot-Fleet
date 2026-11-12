//
// Created by leafy on 10/20/2026.
//

#include "System.h"

System::System() : warehouse(20), tempWarehouse(5), obstacles(warehouse.getWarehouseSize(), warehouse, 10), robots(warehouse) {
    tasks.addTask(Task('A', warehouse));
}

System::~System() = default;

void System::printWarehouse() {
    cout << warehouse.getWarehouseStr();
}

void System::printTempWarehouse() {
    cout << tempWarehouse.getTempWarehouseStr();
}

void System::runProcess() {

    int selection_main{};
    int numSteps = 1;

    do {
        int selection_tasks{};

        int selection_config{};
        int temp_numSteps{};
        int temp_numObstacles{};
        int temp_warehouseSize{};
        int temp_seed{};
        Point temp_pickupCoord{};
        Point temp_dropoffCoord{};

        warehouse.drawTasks(tasks.getTasks());
        warehouse.drawRobots(robots.getRobots());
        printWarehouse();

        for (auto& task : tasks.getTasks()) {
            cout << task.getPickupPosition().x << " " << task.getPickupPosition().y << endl;
            cout << task.getDropoffPosition().x << " " << task.getDropoffPosition().y << endl;
        }

        cout << endl;
        cout << "1). Advance simulation " << numSteps << " step" << endl;
        cout << "2). Create a new task" << endl;
        cout << "3). Get status of robots" << endl;
        cout << "4). Configuration" << endl;
        cout << "5). Exit" << endl;

        selection_main = getSelection(1, 5, true);

        // Main menu logic
        if (selection_main == 1) {
            // Advance simulation
            for (auto& robot : robots.getRobots()) {
                if (robot.getStatus() == "idle" && tasks.getSize()) {
                    Task task = tasks.popTask();
                    robot.pushPath(robot.searchPath(warehouse, task));
                    robot.pushPath(robot.searchPath(warehouse, robot.getPosition(), task.getPickupPosition()));
                }
                else if (robot.getStatus() == "idle" && !tasks.getSize()) {
                    cout << "Error: No existing tasks" << endl;
                }

                // if (robot.getBattery() >= 50) {
                    warehouse.updateRobots(robots.getRobots());
                // }
            }
        }
        else if (selection_main == 2) {
            // Assign a task to a robot
            cout << "1). Randomize pickup/dropoff locations" << endl;
            cout << "2). Manually input pickup/dropoff locations" << endl;
            cout << "3). Main menu" << endl;
            selection_tasks = getSelection(1, 3, true);
        }
        else if (selection_main == 3) {
            // Print the status of each robot
            for (const auto& robot : robots.getRobots()) {
                cout << "Robot " << robot.getName() << " -> " << "Station " << robot.getStatus() << endl;
            }
        }
        else if (selection_main == 4) {
            // Configuration (sub menu)
            cout << "1). Change simulation increment interval" << endl;
            cout << "2). Change number of obstacles" << endl;
            cout << "3). Change warehouse size" << endl;
            cout << "4). Set warehouse seed" << endl;
            cout << "5). Main menu" << endl;
            selection_config = getSelection(1, 5, true);
        }
        else if (selection_main == 5) {
            // Exit
            cout << "Exiting..." << endl;
        }


        // Logic for tasks sub menu
        if (selection_tasks == 1) {
            mt19937 seed(warehouse.getWarehouseSeed());

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

            if (tasks.getSize()) {
                tasks.addTask(Task(static_cast<char>(tasks.getTasks().back().getName() + 1) ,pickupCoord, dropoffCoord));
            }
            else {
                tasks.addTask(Task('A', pickupCoord, dropoffCoord));
            }
        }
        else if (selection_tasks == 2) {
            // Ask the user for a valid pickup location
            do {
                temp_pickupCoord.x = getSelection(1, warehouse.getWarehouseSize(), true, "Pickup X: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_pickupCoord.y = getSelection(1, warehouse.getWarehouseSize(), true, "Pickup Y: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_pickupCoord.x--;
                temp_pickupCoord.y--;
                if (!warehouse.isAir(temp_pickupCoord)) {
                    cout << "Error: Coordinate is occupied" << endl;
                }
            } while (!warehouse.isAir(temp_pickupCoord));

            // Ask the user for a valid dropoff location
            do {
                temp_dropoffCoord.x = getSelection(1, warehouse.getWarehouseSize(), true, "Dropoff X: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_dropoffCoord.y = getSelection(1, warehouse.getWarehouseSize(), true, "Dropoff Y: ", "Error: Invalid pickup location (1-" + to_string(warehouse.getWarehouseSize()) + ")");
                temp_dropoffCoord.x--;
                temp_dropoffCoord.y--;
                if (!warehouse.isAir(temp_pickupCoord)) {
                    cout << "Error: Coordinate is occupied" << endl;
                }
            } while (!warehouse.isAir(temp_dropoffCoord));

            // Put the new task on the stack
            if (tasks.getSize()) {
                tasks.addTask(Task(static_cast<char>(tasks.getTasks().back().getName() + 1), temp_pickupCoord, temp_dropoffCoord));
            }
            else {
                tasks.addTask(Task('A', temp_pickupCoord, temp_dropoffCoord));
            }
        }


        // Logic for config sub menu
        if (selection_config == 1) {
            cout << "Current increment interval: " << numSteps << endl;
            temp_numSteps = getSelection(1, 10, true, "Steps: ", "Error: Invalid step count (1-10)");
            numSteps = temp_numSteps;
        }
        else if (selection_config == 2) {
            cout << "Current number of obstacles: " << obstacles.getNumObstacles() << endl;
            temp_numObstacles = getSelection(0, 0, false, "Number of obstacles: ", "Error: Invalid number of obstacles (0+)");
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(temp_numObstacles, warehouse, warehouse.getWarehouseSeed());
        }
        else if (selection_config == 3) {
            cout << "Current warehouse size: " << warehouse.getWarehouseSize() << endl;
            temp_warehouseSize = getSelection(5, 0, false, "Warehouse size: ", "Error: Invalid warehouse size (5+)");
            warehouse = Warehouse(temp_warehouseSize);
            obstacles = ObstacleManager(temp_warehouseSize, warehouse, warehouse.getWarehouseSeed());
        }
        else if (selection_config == 4) {
            cout << "Current seed: " << warehouse.getWarehouseSeed() << endl;
            temp_seed = getSelection(0, 0, false, "Set seed: ", "Error: Invalid seed (0+)");
            warehouse = Warehouse(warehouse.getWarehouseSize());
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, temp_seed);
        }

    } while (selection_main != 5);
}

int System::getSelection(const int min, const int max, const bool bounded) {
    return getSelection(min, max, bounded, "Enter selection: ", "Error: Invalid input: ");
}

int System::getSelection(const int min, const int max, const bool bounded, const string& text, const string& error) {
    int selection{};
    bool flag{};

    do {
        if (!cin || flag) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << error << endl;
        }
        cout << text;

        // If bounded, then selection must be between start and end
        if (bounded) {
            flag = !(cin >> selection) || selection < min || selection > max;
        }
        // If unbounded, then either selection must be greater than start, or less than end
        else {
            // If both min and max == 0, arbitrarily assume selection must be positive
            if (min == 0 && max == 0) {
                flag = !(cin >> selection) || selection < min;
            }
            // If start == 0, then selection must be less than end
            else if (min == 0) {
                flag = !(cin >> selection) || selection > max;
            }
            // If end == 0, then selection must be greater than start
            else if (max == 0) {
                flag = !(cin >> selection) || selection < min;
            }
            // Debugging
            else {
                cerr << "Error: Invalid selection code" << endl;
            }
        }
    } while (flag);

    return selection;
}