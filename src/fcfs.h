#ifndef FCFS_H
#define FCFS_H

#include <iostream>
#include <vector>
#include "load-data.h"

using namespace std;

struct ProcessOnCpuType {
    int arrivalTime;
    int departureTime;
    string name;
    int duration;
};

class Fcfs {
    private:
        vector<ProcessOnCpuType> timeline;

    public:
        Fcfs();
        Fcfs(vector<ProcessType> process);

        vector<ProcessOnCpuType> getTimeline();
        void printTimeline();
};

#endif // FCFS_H