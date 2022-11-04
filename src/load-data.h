#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct ProcessType {
    string name;
    int arrivalTime, duration;
};

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