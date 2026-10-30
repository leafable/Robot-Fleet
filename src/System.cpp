//
// Created by leafy on 10/20/2026.
//

#include "System.h"

System::System() : warehouse(20), tempWarehouse(5), obstacles(warehouse.getWarehouseSize(), warehouse) {

}
System::~System() {

}

void System::printWarehouse() {
    cout << warehouse.getWarehouseStr(*obstacles.getObstacles());
}

void System::printTempWarehouse() {
    cout << tempWarehouse.getTempWarehouseStr();
}

void System::runProcess() {

    int selection_1{};

    do {
        int selection_1_2{};

        int selection_1_3{};
        int selection_1_3_1{};
        int selection_1_3_2{};
        int selection_1_3_3{};

        printWarehouse();

        cout << endl;
        cout << "1). Advance simulation 1 step" << endl;
        cout << "2). Assign a task to a robot" << endl;
        cout << "3). Configuration" << endl;
        cout << "4). Exit" << endl;

        selection_1 = getSelection(1, 4, true);

        // Main menu
        if (selection_1 == 1) {
            // Advance simulation 1 step
        }
        else if (selection_1 == 2) {
            // Assign a task to a robot
        }
        else if (selection_1 == 3) {
            cout << "1). Change warehouse size" << endl;
            cout << "2). Change number of obstacles" << endl;
            cout << "3). Set warehouse seed" << endl;
            selection_1_3 = getSelection(1, 3, true);
        }
        else if (selection_1 == 4) {
            cout << "Exiting..." << endl;
        }


        // Sub menu #2
        if (selection_1_2 == 1) {

        }
        else if (selection_1_2 == 2) {

        }


        // Sub menu #3
        if (selection_1_3 == 1) {
            cout << "Current warehouse size: " << warehouse.getWarehouseSize() << endl;
            selection_1_3_1 = getSelection(5, 0, false, "Warehouse size: ", "Error: Invalid warehouse size (5+)");
            warehouse = Warehouse(selection_1_3_1);
            obstacles = ObstacleManager(selection_1_3_1, warehouse, obstacles.getSeed());
        }
        else if (selection_1_3 == 2) {
            cout << "Current number of obstacles: " << obstacles.getNumObstacles() << endl;
            selection_1_3_2 = getSelection(0, 0, false, "Number of obstacles: ", "Error: Invalid number of obstacles (0+)");
            obstacles = ObstacleManager(selection_1_3_2, warehouse, obstacles.getSeed());
        }
        else if (selection_1_3 == 3) {
            cout << "Current seed: " << obstacles.getSeed() << endl;
            selection_1_3_3 = getSelection(0, 0, false, "Set seed: ", "Error: Invalid seed (0+)");
            obstacles = ObstacleManager(obstacles.getNumObstacles(), warehouse, selection_1_3_3);
        }

    } while (selection_1 != 4);
}

int System::getSelection(int min, int max, bool bounded) {
    return getSelection(min, max, bounded, "Enter selection: ", "Error: Invalid input: ");
}

int System::getSelection(int min, int max, bool bounded, const string& text, const string& error) {
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
            // If both min and max == 0, then selection must be greater than min (arbitrary)
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