#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <iostream>
#include <vector>
#include <fstream>
#include "types.h"

using namespace std;

class LoadData {
    private:
        vector<ProcessType> processes;

    public:
        LoadData();
        LoadData(string path);

        vector<ProcessType> getProcesses();

        void printProcesses();
};

#endif // LOAD_DATA_H