#ifndef TYPES_H
#define TYPES_H

#include <iostream>

using namespace std;

struct ProcessType {
    string id;
    int arrivalTime, duration;
};

struct ProcessOnCpuType {
    int arrivalTime, entryTime, departureTime, duration;
    string processId;
};

struct MetricType {
    int value;
    string processId;
};

#endif // TYPES_H
