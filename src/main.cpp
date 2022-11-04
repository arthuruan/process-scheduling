#include <iostream>
#include "load-data.h"

int main(void) {
    LoadData loadData("./instances/process-1.txt");

    loadData.printProcesses();

    return 0;
}