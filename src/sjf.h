#ifndef SJF_H
#define SJF_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "types.h"

using namespace std;

class Sjf {
    private:
        vector<ProcessOnCpuType> timeline;

    public:
        Sjf();
        Sjf(vector<ProcessType> process);

        vector<ProcessOnCpuType> getTimeline();
        void printTimeline();
};

#endif // SJF_H