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

int getGroupedTimelineIndexByProcessId(vector< vector<ProcessOnCpuType> > &groupedTimeline, string &processId) {
    int index = -1;

    for (int i = 0; i < groupedTimeline.size(); i++) {
        vector<ProcessOnCpuType> group = groupedTimeline[i];
        for (int j = 0; j < group.size(); j++) {
            if (group[j].processId == processId) {
                index = i;
                break;
            }
        }
    }

    return index;
}

float calculateMetricsAvg(vector<MetricType> &metrics) {
    int sum = 0;
    for (int i = 0; i < metrics.size(); i++) {
        sum += metrics[i].value;
    }
    float result = (float)sum / (float)metrics.size();
    return result;
}

vector<MetricType> calculateResponseTimeGroup(vector<ProcessOnCpuType> &timeline) {
    vector<MetricType> responseTimeGroup;

    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        MetricType metric;
        
        int index = getMetricIndexByProcessId(responseTimeGroup, processOnCpu.processId);

        MetricType metricByProcessId = index >= 0 ? responseTimeGroup[index] : metric;
        if (metricByProcessId.processId.empty()) {
            metric.processId = processOnCpu.processId;
            metric.value = processOnCpu.entryTime;
            responseTimeGroup.push_back(metric);
        }
    }

    return responseTimeGroup;
}

vector<MetricType> calculateTurnaroundTimeGroup(vector<ProcessOnCpuType> &timeline) {
    vector<MetricType> turnaroundTimeGroup;

    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        MetricType metric;

        int index = getMetricIndexByProcessId(turnaroundTimeGroup, processOnCpu.processId);

        MetricType metricByProcessId = index >= 0 ? turnaroundTimeGroup[index] : metric;
        if (metricByProcessId.processId.empty()) {
            metric.processId = processOnCpu.processId;
            metric.value = processOnCpu.departureTime;
            turnaroundTimeGroup.push_back(metric);
        } else {
            turnaroundTimeGroup[index].value = metricByProcessId.value > processOnCpu.departureTime ? metricByProcessId.value : processOnCpu.departureTime;
        }
    }

    return turnaroundTimeGroup;
}

vector< vector<ProcessOnCpuType> > groupByProcessId(vector<ProcessOnCpuType> &timeline) {
    vector< vector<ProcessOnCpuType> > groupedTimeline;

    for (int i = 0; i < timeline.size(); i++) {
        ProcessOnCpuType processOnCpu = timeline[i];
        vector<ProcessOnCpuType> processOnCpuGroup;

        int index = getGroupedTimelineIndexByProcessId(groupedTimeline, processOnCpu.processId);

        vector<ProcessOnCpuType> processOnCpuGroupByProcessId = index >= 0 ? groupedTimeline[index] : processOnCpuGroup;
        if (processOnCpuGroupByProcessId.empty()) {
            processOnCpuGroup.push_back(processOnCpu);
            groupedTimeline.push_back(processOnCpuGroup);
        } else {
            groupedTimeline[index].push_back(processOnCpu);
        }
    }
    return groupedTimeline;
}

vector<MetricType> calculateWaitingTimeGroup(vector<ProcessOnCpuType> &timeline) {
    vector<MetricType> waitingTimeGroup;
    vector< vector<ProcessOnCpuType> > groupedTimeline = groupByProcessId(timeline);

    for (int i = 0; i < groupedTimeline.size(); i++) {
        vector<ProcessOnCpuType> processOnCpuGroup = groupedTimeline[i];
        MetricType metric;

        for (int j = 0; j < processOnCpuGroup.size(); j++) {
            ProcessOnCpuType processOnCpu = processOnCpuGroup[j];
            if (j == 0) {
                metric.processId = processOnCpu.processId;
                metric.value = processOnCpu.entryTime - processOnCpu.arrivalTime;
            } else {
                metric.value = processOnCpu.entryTime - processOnCpuGroup[j - 1].departureTime;
            }
        }
        waitingTimeGroup.push_back(metric);
    }

    return waitingTimeGroup;
}

Metrics::Metrics(vector<ProcessOnCpuType> timeline, string algorithm) {
    this->algorithm = algorithm;
    responseTimeGroup = calculateResponseTimeGroup(timeline);
    turnaroundTimeGroup = calculateTurnaroundTimeGroup(timeline);
    waitingTimeGroup = calculateWaitingTimeGroup(timeline);
}

vector<MetricType> Metrics::getWaitingTimeGroup() {
    return waitingTimeGroup;
}

vector<MetricType> Metrics::getTurnaroundTimeGroup() {
    return turnaroundTimeGroup;
}

vector<MetricType> Metrics::getResponseTimeGroup() {
    return responseTimeGroup;
}

void Metrics::printMetrics() {
    float avgTurnaroundTime = calculateMetricsAvg(turnaroundTimeGroup);
    float avgResponseTime = calculateMetricsAvg(responseTimeGroup);
    float avgWaitingTime = calculateMetricsAvg(waitingTimeGroup);
    printf("%s %.1f %.1f %.1f\n", algorithm.c_str(), avgTurnaroundTime, avgResponseTime, avgWaitingTime);
}