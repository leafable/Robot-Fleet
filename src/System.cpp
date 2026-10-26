//
// Created by leafy on 10/20/2026.
//

#include "System.h"

System::System() : tempWarehouse(5) {

}
System::~System() {

}

void System::printWarehouse() {
    cout << tempWarehouse.getTempWarehouseStr();
}