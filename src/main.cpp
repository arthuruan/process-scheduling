#include <iostream>
#include "load-data.h"
#include "fcfs.h"
#include "sjf.h"
#include "rr.h"
#include "metrics.h"

const int QUANTUM = 2;

int main(void) {
    LoadData loadData("./instances/process-1.txt");
    cout << "PROCESSES" << endl << endl;
    loadData.printProcesses();

    Fcfs fcfs(loadData.getProcesses());
    Sjf sjf(loadData.getProcesses());
    Rr rr(loadData.getProcesses(), QUANTUM);

    cout << "--------------------------------" << endl;
    cout << "TIMELINE" << endl << endl;
    fcfs.printTimeline();
    sjf.printTimeline();
    rr.printTimeline();
    cout << "--------------------------------" << endl;

    Metrics metricsFcfs(fcfs.getTimeline(), "FCFS");
    Metrics metricsSjf(sjf.getTimeline(), "SJF");
    Metrics metricsRr(rr.getTimeline(), "RR");

    cout << "METRICS" << endl << endl;

    metricsFcfs.printMetrics();
    metricsSjf.printMetrics();
    metricsRr.printMetrics();

    return 0;
}