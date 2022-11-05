#include "fcfs.h"
#include <algorithm>

bool compareByArriveTime(const ProcessType &a, const ProcessType &b) {
    return a.arrivalTime < b.arrivalTime;
}

vector<ProcessType> sortByArriveTime(vector<ProcessType> &processes) {
    sort(processes.begin(), processes.end(), compareByArriveTime);
    return processes;
}

Fcfs::Fcfs(vector<ProcessType> processesParam) {
    vector<ProcessType> processes = sortByArriveTime(processesParam);

    int currentTime = 0;
    
    for (int i = 0; i < processes.size(); i++) {
        ProcessType process = processes[i];
        ProcessOnCpuType processOnCpu;
        
        processOnCpu.name = process.name;

        processOnCpu.arrivalTime = currentTime;
        processOnCpu.departureTime = currentTime + process.duration;
        processOnCpu.duration = process.duration;
        
        timeline.push_back(processOnCpu);
        currentTime += process.duration;
    }
}


vector<ProcessOnCpuType> Fcfs::getTimeline() {
    return timeline;
}

void Fcfs::printTimeline() {
    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType process = timeline[i];
        cout << process.name << ": " << endl
            << "\t arrival: " << process.arrivalTime << endl
            << "\t departure: " << process.departureTime << endl << endl;
    }
}