#include "fcfs.h"

bool compareFcfs(const ProcessType &a, const ProcessType &b) {
    return a.arrivalTime < b.arrivalTime;
}

vector<ProcessType> sortFcfsByArriveTime(vector<ProcessType> &processes) {
    sort(processes.begin(), processes.end(), compareFcfs);
    return processes;
}

Fcfs::Fcfs(vector<ProcessType> processesParam) {
    vector<ProcessType> processes = sortFcfsByArriveTime(processesParam);

    int currentTime = 0;
    
    for (int i = 0; i < processes.size(); i++) {
        ProcessType process = processes[i];
        ProcessOnCpuType processOnCpu;

        processOnCpu.processId = process.id;

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
    cout << "FCFS: " << timeline[0].arrivalTime;
    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        cout << " [" << processOnCpu.processId << "] " << processOnCpu.departureTime;
    }
    cout << endl << endl;
}