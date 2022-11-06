#include "rr.h"

bool compareRr(const ProcessType &a, const ProcessType &b) {
    return a.arrivalTime < b.arrivalTime;
}

vector<ProcessType> sortRrByArriveTime(vector<ProcessType> &processes) {
    sort(processes.begin(), processes.end(), compareRr);
    return processes;
}

Rr::Rr(vector<ProcessType> processesParam, int quantum) {
    vector<ProcessType> processes = sortRrByArriveTime(processesParam);

    int currentTime = 0;

    while(processes.size() > 0) {
        ProcessType process = processes[0];
        ProcessOnCpuType processOnCpu;

        if (quantum < process.duration) {
            processOnCpu.name = process.name;
            processOnCpu.arrivalTime = currentTime;
            processOnCpu.departureTime = currentTime + quantum;
            processOnCpu.readyQueueTime = -1; // TODO
            processOnCpu.duration = quantum;

            ProcessType leftoverProcess;
            leftoverProcess.name = process.name;
            leftoverProcess.arrivalTime = process.arrivalTime;
            leftoverProcess.duration = process.duration - quantum;
            processes.push_back(leftoverProcess);
        } else {
            processOnCpu.name = process.name;
            processOnCpu.arrivalTime = currentTime;
            processOnCpu.departureTime = currentTime + process.duration;
            processOnCpu.readyQueueTime = -1; // TODO
            processOnCpu.duration = process.duration;
        }
        timeline.push_back(processOnCpu);
        currentTime += processOnCpu.duration;

        processes.erase(processes.begin());
    }
}

vector<ProcessOnCpuType> Rr::getTimeline() {
    return timeline;
}

void Rr::printTimeline() {
    cout << "RR: " << timeline[0].arrivalTime;
    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType process = timeline[i];
        cout << " [" << process.name << "] " << process.departureTime;
    }
    cout << endl << endl;
}