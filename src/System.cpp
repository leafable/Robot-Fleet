//
// Created by leafy on 10/20/2026.
//

#include "System.h"

System::System() : obstacles(10), warehouse(20) {

}
System::~System() {

}

void System::printWarehouse() {
    cout << warehouse.getWarehouseStr(obstacles);
}

void System::printAllCoords() {
    obstacles.printAllCoords();
}