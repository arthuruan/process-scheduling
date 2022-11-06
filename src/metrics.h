#ifndef METRICS_H
#define METRICS_H

#include <iostream>
#include <vector>
// #include <algorithm>
#include "types.h"

using namespace std;

class Metrics {
    private:
        string algorithm;
        vector<MetricType> avgWaitingTime;
        vector<MetricType> avgTurnaroundTime;
        vector<MetricType> avgResponseTime;

    public:
        Metrics();
        Metrics(vector<ProcessOnCpuType> timeline, string algorithm);

        vector<MetricType> getAvgWaitingTime();
        vector<MetricType> getAvgTurnaroundTime();
        vector<MetricType> getAvgResponseTime();
        void printMetrics();
};

#endif // METRICS_H