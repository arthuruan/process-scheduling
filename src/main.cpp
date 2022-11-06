#include <iostream>
#include "load-data.h"
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"

int main(void) {
    LoadData loadData("./instances/process-1.txt");

    Fcfs fcfs(loadData.getProcesses());
    Sjf sjf(loadData.getProcesses());
    Rr rr(loadData.getProcesses(), 2);

    fcfs.printTimeline();
    sjf.printTimeline();
    rr.printTimeline();

    // loadData.printProcesses();

    return 0;
}