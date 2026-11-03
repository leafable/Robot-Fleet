//
// Created by leafy on 10/20/2026.
//

#include "System.h"

System::System() : warehouse(20), tempWarehouse(5), obstacles(warehouse.getWarehouseSize(), warehouse, 5) {

}
System::~System() {

}

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

        printWarehouse();

        cout << endl;
        cout << "1). Advance simulation " << numSteps << " step" << endl;
        cout << "2). Assign a task to a robot" << endl;
        cout << "3). Configuration" << endl;
        cout << "4). Exit" << endl;

        selection_main = getSelection(1, 4, true);

        // Main menu
        if (selection_main == 1) {
            // Advance simulation (no sub menu?)

        }
        else if (selection_main == 2) {
            // Assign a task to a robot (sub menu)

        }
        else if (selection_main == 3) {
            // Configuration (sub menu)
            cout << "1). Change simulation increment interval" << endl;
            cout << "2). Change number of obstacles" << endl;
            cout << "3). Change warehouse size" << endl;
            cout << "4). Set warehouse seed" << endl;
            cout << "5). Main menu" << endl;
            selection_config = getSelection(1, 5, true);
        }
        else if (selection_main == 4) {
            // Exit
            cout << "Exiting..." << endl;
        }


        // Logic for tasks sub menu
        if (selection_tasks == 1) {

        }
        else if (selection_tasks == 2) {

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
            obstacles = ObstacleManager(temp_numObstacles, warehouse, obstacles.getSeed());
        }
        else if (selection_config == 3) {
            cout << "Current warehouse size: " << warehouse.getWarehouseSize() << endl;
            temp_warehouseSize = getSelection(5, 0, false, "Warehouse size: ", "Error: Invalid warehouse size (5+)");
            warehouse = Warehouse(temp_warehouseSize);
            obstacles = ObstacleManager(temp_warehouseSize, warehouse, obstacles.getSeed());
        }
        else if (selection_config == 4) {
            cout << "Current seed: " << obstacles.getSeed() << endl;
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