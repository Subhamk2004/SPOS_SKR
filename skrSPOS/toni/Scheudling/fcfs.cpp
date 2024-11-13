#include <bits/stdc++.h>
using namespace std;

void findCompletionTime(int n, int at[], int bt[], int completion[], int start[]) {
    completion[0] = at[0] + bt[0];
    start[0] = at[0];
    
    for(int i = 1; i < n; i++) {
        start[i] = max(completion[i-1], at[i]);  // The start time for each process
        completion[i] = start[i] + bt[i];
    }
}

void findTurnAroundTime(int n, int at[], int completion[], int tat[]) {
    for(int i = 0; i < n; i++) {
        tat[i] = completion[i] - at[i];
    }
}

void findWaitingTime(int n, int at[], int bt[], int completion[], int wt[]) {
    for(int i = 0; i < n; i++) {
        wt[i] = completion[i] - at[i] - bt[i];
    }
}

void printGanttChart(int n, int start[], int bt[], int completion[]) {
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";
    
    // Top row with process numbers
    for (int i = 0; i < n; i++) {
        cout << "|  P" << (i + 1) << "  ";
    }
    cout << "|\n";

    cout << "-------------------------------------------------\n";

    // Bottom row with start and end times
    for (int i = 0; i < n; i++) {
        cout << start[i] << "______";
    }
    cout << completion[n - 1] << "\n";
}

void findAvgTime(int n, int at[], int bt[]) {
    int completion[n], wt[n], tat[n], start[n];
    
    findCompletionTime(n, at, bt, completion, start);
    findTurnAroundTime(n, at, completion, tat);
    findWaitingTime(n, at, bt, completion, wt);

    int tavg = 0, wavg = 0;

    cout << "\nProcess No. Arrival Time Burst Time Start Time Completion Time Wait Time Turnaround Time\n";
    for(int i = 0; i < n; i++) {
        wavg += wt[i];
        tavg += tat[i];
        
        cout << (i+1) << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << start[i] << "\t\t" 
             << completion[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
    cout << "Average Waiting Time: " << ((float)wavg / (float)n) << endl;
    cout << "Average Turnaround Time: " << ((float)tavg / (float)n) << endl;

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


//This code implements the First Come First Serve (FCFS) CPU scheduling algorithm. Let me explain it in detail:

//Purpose:


//This program simulates how a CPU scheduler would process different tasks/processes that arrive at different times
//It calculates various time metrics important in CPU scheduling
//It visualizes the scheduling using a Gantt chart


//Key Terms Used:


//AT (Arrival Time): When a process arrives in the system
//BT (Burst Time): How long a process needs to complete
//CT (Completion Time): When a process finishes
//TAT (Turnaround Time): Total time from arrival to completion (CT - AT)
//WT (Waiting Time): Time process waits before starting (TAT - BT)



