#ifndef METRICS_H
#define METRICS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include "types.h"

using namespace std;

class Metrics {
    private:
        string algorithm;
        vector<MetricType> waitingTimeGroup;
        vector<MetricType> turnaroundTimeGroup;
        vector<MetricType> responseTimeGroup;

    public:
        Metrics();
        Metrics(vector<ProcessOnCpuType> timeline, string algorithm);

        vector<MetricType> getWaitingTimeGroup();
        vector<MetricType> getTurnaroundTimeGroup();
        vector<MetricType> getResponseTimeGroup();
        void printMetrics();
};

#endif // METRICS_H