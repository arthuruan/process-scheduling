#include <iostream>
#include "load-data.h"
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"
#include "metrics.h"

int main(void) {
    LoadData loadData("./instances/process-1.txt");
    // loadData.printProcesses();

    Fcfs fcfs(loadData.getProcesses());
    Sjf sjf(loadData.getProcesses());
    Rr rr(loadData.getProcesses(), 2);

    fcfs.printTimeline();
    sjf.printTimeline();
    rr.printTimeline();

    Metrics metricsRr(rr.getTimeline(), "RR");

    metricsRr.printMetrics();

    return 0;
}