#include <bits/stdc++.h>
using namespace std;

// Function to find the Completion Time for each process
void findCompletionTime(int n, int at[], int bt[], int completion[], int start[]) {
    // Sort processes based on Arrival Time and Burst Time (for SJF)
    vector<pair<int, pair<int, int>>> processes;
    for (int i = 0; i < n; i++) {
        processes.push_back({at[i], {bt[i], i}});
    }
    sort(processes.begin(), processes.end());

    start[processes[0].second.second] = processes[0].first;
    completion[processes[0].second.second] = start[processes[0].second.second] + processes[0].second.first;

    for (int i = 1; i < n; i++) {
        int idx = processes[i].second.second;
        start[idx] = max(completion[processes[i - 1].second.second], processes[i].first);
        completion[idx] = start[idx] + processes[i].second.first;
    }
}

// Function to find the Turnaround Time for each process
void findTurnAroundTime(int n, int at[], int completion[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = completion[i] - at[i]; // TAT = CT - AT
    }
}

// Function to find the Waiting Time for each process
void findWaitingTime(int n, int bt[], int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i]; // WT = TAT - BT
    }
}

// Function to print the Gantt Chart for the processes based on increasing time
void printGanttChart(int n, int start[], int bt[], int completion[]) {
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";

    // Sort processes by start time for time-based ordering in the Gantt chart
    vector<pair<int, int>> timeline;
    for (int i = 0; i < n; i++) {
        timeline.push_back({start[i], i});
    }
    sort(timeline.begin(), timeline.end());

    // Top row with process numbers
    for (int i = 0; i < n; i++) {
        int idx = timeline[i].second;
        cout << "|  P" << (idx + 1) << "  ";
    }
    cout << "|\n";

    cout << "-------------------------------------------------\n";

    // Bottom row with start and end times in time order
    for (int i = 0; i < n; i++) {
        int idx = timeline[i].second;
        cout << start[idx] << "      ";
    }
    cout << completion[timeline.back().second] << "\n";
}

// Function to find and display average waiting and turnaround times
void findAvgTime(int n, int at[], int bt[]) {
    int completion[n], wt[n], tat[n], start[n];
    
    findCompletionTime(n, at, bt, completion, start);
    findTurnAroundTime(n, at, completion, tat);
    findWaitingTime(n, bt, tat, wt);

    int totalWt = 0, totalTat = 0;

    cout << "\nProcess No.\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tWait Time\tTurnaround Time\n";
    for(int i = 0; i < n; i++) {
        totalWt += wt[i];
        totalTat += tat[i];
        
        cout << "P" << (i+1) << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << start[i] << "\t\t" 
             << completion[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    cout << "Average Waiting Time: " << ((float)totalWt / n) << endl;
    cout << "Average Turnaround Time: " << ((float)totalTat / n) << endl;

    // Print Gantt Chart
    printGanttChart(n, start, bt, completion);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int at[n], bt[n];
    for(int i = 0; i < n; i++) {
        cout << "Enter the Arrival Time and Burst Time of process " << (i+1) << ": ";
        cin >> at[i] >> bt[i];
    }

    findAvgTime(n, at, bt);
    return 0;
}

//shortest job first
