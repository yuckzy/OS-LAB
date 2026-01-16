#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>

using namespace std;

struct Process {
    int id;
    double burstTime;
    double remainingTime;
    double arrivalTime;
    double completionTime;
    double waitingTime;
    double turnaroundTime;
};

int main() {
    double burstTimes[] = {99.99, 107.9, 143.77, 20.24, 50.55, 66.66};
    double quantum = 25.0;
    int n = 6;
    
    vector<Process> processes;
    queue<int> readyQueue;
    
    // Initialize processes
    for (int i = 0; i < n; i++) {
        Process p;
        p.id = i + 1;
        p.burstTime = burstTimes[i];
        p.remainingTime = burstTimes[i];
        p.arrivalTime = 0;
        p.completionTime = 0;
        p.waitingTime = 0;
        p.turnaroundTime = 0;
        processes.push_back(p);
        readyQueue.push(i);
    }
    
    double currentTime = 0;
    vector<pair<double, int>> ganttChart; // (startTime, processId)
    vector<double> ganttEndTimes;
    
    // Round Robin Scheduling
    cout << "=== ROUND ROBIN SCHEDULING ===" << endl;
    cout << "Quantum Time: " << quantum << endl;
    cout << "\nBurst Times:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << (i + 1) << ": " << fixed << setprecision(2) << burstTimes[i] << endl;
    }
    cout << endl;
    
    while (!readyQueue.empty()) {
        int processIdx = readyQueue.front();
        readyQueue.pop();
        
        // Record gantt chart
        ganttChart.push_back({currentTime, processes[processIdx].id});
        
        // Process execution
        if (processes[processIdx].remainingTime > quantum) {
            currentTime += quantum;
            processes[processIdx].remainingTime -= quantum;
            readyQueue.push(processIdx);
        } else {
            currentTime += processes[processIdx].remainingTime;
            processes[processIdx].remainingTime = 0;
            processes[processIdx].completionTime = currentTime;
        }
        
        ganttEndTimes.push_back(currentTime);
    }
    
    // Calculate waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    }
    
    // Display Gantt Chart
    cout << "\n=== GANTT CHART ===" << endl;
    cout << "\n";
    for (int i = 0; i < (int)ganttChart.size(); i++) {
        cout << "-------";
    }
    cout << "-" << endl << "|";
    for (int i = 0; i < (int)ganttChart.size(); i++) {
        cout << "  P" << ganttChart[i].second << "  |";
    }
    cout << endl;
    for (int i = 0; i < (int)ganttChart.size(); i++) {
        cout << "-------";
    }
    cout << "-" << endl << "0";
    for (int i = 0; i < (int)ganttEndTimes.size(); i++) {
        cout << setw(7) << fixed << setprecision(0) << ganttEndTimes[i];
    }
    cout << endl;
    
    // Display Process Details
    cout << "\n=== PROCESS DETAILS ===" << endl;
    cout << left << setw(12) << "Process" 
         << setw(15) << "Burst Time" 
         << setw(18) << "Completion Time" 
         << setw(15) << "Turnaround Time" 
         << setw(15) << "Waiting Time" << endl;
    cout << string(70, '-') << endl;
    
    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << ("P" + to_string(processes[i].id))
             << setw(15) << fixed << setprecision(2) << processes[i].burstTime
             << setw(18) << fixed << setprecision(2) << processes[i].completionTime
             << setw(15) << fixed << setprecision(2) << processes[i].turnaroundTime
             << setw(15) << fixed << setprecision(2) << processes[i].waitingTime << endl;
    }
    
    // Calculate averages
    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;
    
    cout << string(70, '-') << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avgTurnaroundTime << endl;
    
    return 0;
}
