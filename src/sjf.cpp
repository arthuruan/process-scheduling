#include "sjf.h"

bool compareSjf(const ProcessType &a, const ProcessType &b) {
    return a.arrivalTime == b.arrivalTime ? a.duration < b.duration : a.arrivalTime < b.arrivalTime;
}

vector<ProcessType> sortSjfByArriveAndDurationTime(vector<ProcessType> &processes) {
    sort(processes.begin(), processes.end(), compareSjf);
    return processes;
}

ProcessType getSmallerProcess(vector<ProcessType> &processes) {
    int smaller = 0;
    for(int i = 0; i < processes.size(); i++) {
        if(processes[i].duration < processes[smaller].duration) {
            smaller = i;
        }
    }
    return processes[smaller];
}

int getIndexThroughName(vector<ProcessType> &processes, string &processId) {
    int index = 0;
    for(int i = 0; i < processes.size(); i++) {
        if(processes[i].id == processId) {
            index = i;
            break;
        }
    }
    return index;
}

Sjf::Sjf(vector<ProcessType> processesParam) {
    vector<ProcessType> processes = sortSjfByArriveAndDurationTime(processesParam);
    int currentTime = 0;

    while(processes.size() > 0) {
        ProcessType smallerProcess = getSmallerProcess(processes); // smaller process duration
        ProcessType firstProcess = processes[0]; // first process in the ready queue

        ProcessOnCpuType processOnCpu;
        if (firstProcess.arrivalTime < smallerProcess.arrivalTime && currentTime < smallerProcess.arrivalTime) {
            processOnCpu.processId = firstProcess.id;
            processOnCpu.arrivalTime = firstProcess.arrivalTime;
            processOnCpu.entryTime = currentTime;
            processOnCpu.departureTime = smallerProcess.arrivalTime < firstProcess.duration ? currentTime + smallerProcess.arrivalTime : currentTime + firstProcess.duration;
            processOnCpu.duration = processOnCpu.departureTime - processOnCpu.entryTime;

            ProcessType leftoverProcess;
            leftoverProcess.id = firstProcess.id;
            leftoverProcess.arrivalTime = firstProcess.arrivalTime;
            leftoverProcess.duration = firstProcess.duration - smallerProcess.arrivalTime;
            processes.push_back(leftoverProcess);
        } else {
            processOnCpu.processId = smallerProcess.id;
            processOnCpu.arrivalTime = smallerProcess.arrivalTime;
            processOnCpu.entryTime = currentTime;
            processOnCpu.departureTime = currentTime + smallerProcess.duration;
            processOnCpu.duration = smallerProcess.duration;
        }
        currentTime += processOnCpu.duration;
        timeline.push_back(processOnCpu);

        int eraseIndex = getIndexThroughName(processes, processOnCpu.processId);
        processes.erase(processes.begin() + eraseIndex);
    }
}

vector<ProcessOnCpuType> Sjf::getTimeline() {
    return timeline;
}

void Sjf::printTimeline() {
    cout << "SJF: " << timeline[0].entryTime;
    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        cout << " [" << processOnCpu.processId << "] " << processOnCpu.departureTime;
    }
    cout << endl << endl;
}