#ifndef FCFS_H
#define FCFS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "types.h"

using namespace std;

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