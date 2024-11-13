#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, tq, time = 0, totalTurnaroundTime = 0, totalWaitingTime = 0;
    cout << "Enter the time quantum: ";
    cin >> tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> arrivalTime(n), burstTime(n), remainingTime(n);
    vector<int> startTime(n, -1), completionTime(n), turnaroundTime(n), waitingTime(n);
    vector<bool> isStarted(n, false);  // Track if a process has started at least once

    deque<int> readyQueue;

    // Input process details
    cout << "Enter the arrival time and burst time of the processes:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        cin >> arrivalTime[i] >> burstTime[i];
        remainingTime[i] = burstTime[i];
    }

    int remain = n;

    // Populate the ready queue initially with all processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (arrivalTime[i] == 0) {
            readyQueue.push_back(i);
        }
    }

    while (remain > 0) {
        // If the ready queue is empty, increment time until a process arrives
        if (readyQueue.empty()) {
            time++;
            // Check if any new processes have arrived at this time
            for (int i = 0; i < n; i++) {
                if (arrivalTime[i] == time && remainingTime[i] > 0) {
                    readyQueue.push_back(i);
                }
            }
            continue;
        }

        // Get the front process in the ready queue
        int i = readyQueue.front();
        readyQueue.pop_front();

        // Record the start time if the process has never started
        if (!isStarted[i]) {
            startTime[i] = time;
            isStarted[i] = true;
        }

        // Execute the process for the time quantum or until completion
        if (remainingTime[i] <= tq) {
            time += remainingTime[i];
            remainingTime[i] = 0;
            completionTime[i] = time;

            // Calculate turnaround time and waiting time
            turnaroundTime[i] = completionTime[i] - arrivalTime[i];
            waitingTime[i] = turnaroundTime[i] - burstTime[i];

            totalTurnaroundTime += turnaroundTime[i];
            totalWaitingTime += waitingTime[i];
            remain--;  // Process is completed
        } else {
            time += tq;
            remainingTime[i] -= tq;
        }

        // Add any newly arrived processes to the ready queue
        for (int j = 0; j < n; j++) {
            if (arrivalTime[j] <= time && remainingTime[j] > 0 &&
                find(readyQueue.begin(), readyQueue.end(), j) == readyQueue.end() && j != i) {
                readyQueue.push_back(j);
            }
        }

        // If the current process is not yet complete, add it back to the queue
        if (remainingTime[i] > 0) {
            readyQueue.push_back(i);
        }
    }

    // Output process information
    cout << "\nProcess\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << (i + 1) << "\t\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" 
             << startTime[i] << "\t\t" << completionTime[i] << "\t\t" 
             << turnaroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    // Calculate and print average waiting time and turnaround time
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnaroundTime / n << endl;

    return 0;
}

//This code implements the Round Robin (RR) scheduling algorithm with a time quantum (tq). It simulates process scheduling in a CPU where each process gets a fixed amount of time (time quantum) to execute. If a process doesn’t finish within its allocated time, it is put back in the queue and will get another chance to execute. The goal of this program is to calculate various metrics like waiting time, turnaround time, and average values for processes.
//Key Components and Explanation

  //  Variables and Data Structures:
     //   arrivalTime[]: Stores the arrival times of processes.
    //    burstTime[]: Stores the burst times (execution times) of processes.
      //  remainingTime[]: Tracks the remaining burst time for each process (decreases as the process executes).
     //   startTime[]: The start time of each process. Initialized to -1 (indicating it hasn't started yet).
     //   completionTime[]: The time when each process finishes executing.
     //   turnaroundTime[]: The total time taken for a process to complete from arrival (calculated as completionTime[i] - arrivalTime[i]).
    //    waitingTime[]: The total waiting time of a process before it starts execution (calculated as turnaroundTime[i] - burstTime[i]).
     //   isStarted[]: A boolean array to track if a process has already started executing.
     //   readyQueue: A queue to hold processes that are ready to execute (this is a deque to allow easy removal from the front and addition to the back).

    // Input:
     //   The program asks for the time quantum (tq), number of processes (n), and the arrival and burst times for each process.

   // Processing Logic:

    //    Initialization: The processes that arrive at time 0 are added to the readyQueue.

    //    Main Loop (while (remain > 0)):

         //   Empty Ready Queue Handling: If the readyQueue is empty, the CPU "waits" (increment the time variable) until a new process arrives. The program checks for newly arrived processes at each time unit and adds them to the queue.

         //   **Process Execution
