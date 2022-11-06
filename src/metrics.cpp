#include "metrics.h"

int getMetricIndexByProcessId(vector<MetricType> &metrics, string &processId) {
    int index = -1;
    for (int i = 0; i < metrics.size(); i++) {
        if (metrics[i].processId == processId) {
            index = i;
            break;
        }
    }
    return index;
}

vector<MetricType> calculateAvgResponseTime(vector<ProcessOnCpuType> &timeline) {
    vector<MetricType> avgResponseTime;

    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        MetricType metric;
        
        int index = getMetricIndexByProcessId(avgResponseTime, processOnCpu.processId);

        MetricType metricByProcessId = index >= 0 ? avgResponseTime[index] : metric;
        if (metricByProcessId.processId.empty()) {
            metric.processId = processOnCpu.processId;
            metric.value = processOnCpu.arrivalTime;
            avgResponseTime.push_back(metric);
        }
    }

    return avgResponseTime;
}

vector<MetricType> calculateAvgTurnaroundTime(vector<ProcessOnCpuType> &timeline) {
    vector<MetricType> avgTurnaroundTime;

    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        MetricType metric;

        int index = getMetricIndexByProcessId(avgTurnaroundTime, processOnCpu.processId);

        MetricType metricByProcessId = index >= 0 ? avgTurnaroundTime[index] : metric;
        if (metricByProcessId.processId.empty()) {
            metric.processId = processOnCpu.processId;
            metric.value = processOnCpu.departureTime;
            avgTurnaroundTime.push_back(metric);
        } else {
            avgTurnaroundTime[index].value = metricByProcessId.value > processOnCpu.departureTime ? metricByProcessId.value : processOnCpu.departureTime;
        }
    }

    return avgTurnaroundTime;
}

Metrics::Metrics(vector<ProcessOnCpuType> timeline, string algorithm) {
    this->algorithm = algorithm;
    avgResponseTime = calculateAvgResponseTime(timeline);
    avgTurnaroundTime = calculateAvgTurnaroundTime(timeline);
}

vector<MetricType> Metrics::getAvgWaitingTime() {
    return avgWaitingTime;
}

vector<MetricType> Metrics::getAvgTurnaroundTime() {
    return avgTurnaroundTime;
}

vector<MetricType> Metrics::getAvgResponseTime() {
    return avgResponseTime;
}

void Metrics::printMetrics() {
    cout << "[" << algorithm << "]" << endl;
    cout << "Average waiting time: " << endl;
    for (int i = 0; i < avgWaitingTime.size(); i++) {
        MetricType metric = avgWaitingTime[i];
        cout << "\t" << metric.processId << ": " << metric.value << endl;
    }
    cout << endl;

    cout << "Average turnaround time: " << endl;
    for (int i = 0; i < avgTurnaroundTime.size(); i++) {
        MetricType metric = avgTurnaroundTime[i];
        cout << "\t" << metric.processId << ": " << metric.value << endl;
    }
    cout << endl;

    cout << "Average response time: " << endl;
    for (int i = 0; i < avgResponseTime.size(); i++) {
        MetricType metric = avgResponseTime[i];
        cout << "\t" << metric.processId << ": " << metric.value << endl;
    }
    cout << endl << endl;
}