#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "load-data.h"
#include <vector>

using namespace std;

LoadData::LoadData(string pathParam) {
    ifstream myfile(pathParam);

    int index;

    if (myfile.is_open()) {
        while (myfile.good()) {
            ProcessType p;

            myfile >> p.arrivalTime;
            myfile >> p.duration;
            p.name = "P" + to_string(index);

            processes.push_back(p);

            index++;
        }
    } else cout << "Unable to open file in path" << pathParam;
}

vector<ProcessType> LoadData::getProcesses() {
    return processes;
}

void LoadData::printProcesses() {
    for (int i = 0; i < processes.size(); i++) {
        ProcessType process = processes[i];
        cout << process.name << ": " << process.arrivalTime << " " << process.duration << endl;
    }
}