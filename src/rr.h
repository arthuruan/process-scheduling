#ifndef RR_H
#define RR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "types.h"

using namespace std;

class Rr {
    private:
        vector<ProcessOnCpuType> timeline;

    public:
        Rr();
        Rr(vector<ProcessType> process, int quantum);

        vector<ProcessOnCpuType> getTimeline();
        void printTimeline();
};

#endif // RR_H