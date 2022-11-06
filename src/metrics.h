#ifndef METRICS_H
#define METRICS_H

#include <iostream>
#include <vector>
// #include <algorithm>
#include "types.h"

using namespace std;

class Metrics {
    public:
        Metrics();
        Metrics(vector<ProcessOnCpuType> timeline);

        int getAverageWaitingTime();
        int getAverageTurnaroundTime();
        int getAverageResponseTime();

        void printMetrics();
};

#endif // METRICS_H