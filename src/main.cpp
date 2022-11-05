#include <iostream>
#include "load-data.h"
#include "fcfs.h"

int main(void) {
    LoadData loadData("./instances/process-1.txt");

    Fcfs fcfs(loadData.getProcesses());

    fcfs.printTimeline();

    // loadData.printProcesses();

    return 0;
}