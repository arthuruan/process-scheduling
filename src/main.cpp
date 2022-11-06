#include <iostream>
#include "load-data.h"
#include "fcfs.h"
#include "sjf.h"

int main(void) {
    LoadData loadData("./instances/process-1.txt");

    Fcfs fcfs(loadData.getProcesses());
    Sjf sjf(loadData.getProcesses());

    fcfs.printTimeline();
    sjf.printTimeline();

    // loadData.printProcesses();

    return 0;
}