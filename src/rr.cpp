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

        processOnCpu.processId = process.id;
        processOnCpu.arrivalTime = process.arrivalTime;
        processOnCpu.entryTime = currentTime;

        if (quantum < process.duration) {
            processOnCpu.departureTime = currentTime + quantum;
            processOnCpu.duration = quantum;

            ProcessType leftoverProcess;
            leftoverProcess.id = process.id;
            leftoverProcess.arrivalTime = process.arrivalTime;
            leftoverProcess.duration = process.duration - quantum;
            processes.push_back(leftoverProcess);
        } else {
            processOnCpu.departureTime = currentTime + process.duration;
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
    cout << "RR: " << timeline[0].entryTime;
    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        cout << " [" << processOnCpu.processId << "] " << processOnCpu.departureTime;
    }
    cout << endl << endl;
}