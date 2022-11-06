#ifndef TYPES_H
#define TYPES_H

#include <iostream>

using namespace std;

struct ProcessType {
    string name;
    int arrivalTime, duration;
};

struct ProcessOnCpuType {
    int arrivalTime, departureTime, readyQueueTime, duration;
    string name;
};

#endif // TYPES_H
