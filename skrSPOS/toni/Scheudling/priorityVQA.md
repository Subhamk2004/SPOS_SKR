### **Code Explanation:**

This C++ program implements the **Preemptive Priority CPU Scheduling Algorithm**. The algorithm prioritizes processes based on their priority values (lower number indicates higher priority). It is **preemptive**, meaning that a running process can be interrupted if a higher priority process arrives. If two processes have the same priority, they are executed in the order of their arrival time, effectively following the **First Come First Serve (FCFS)** rule for equal priorities.

### **Key Concepts:**
- **Arrival Time (AT)**: The time at which a process arrives in the ready queue.
- **Burst Time (BT)**: The amount of CPU time required by the process for execution.
- **Priority**: A numeric value where lower numbers indicate higher priority.
- **Preemption**: The ability to interrupt a currently running process if a higher priority process arrives.
- **Remaining Time**: The time left for a process to complete (used to implement preemption).

---

### **Functions:**

#### 1. **`findAvgTime`**:
   This function simulates the preemptive priority scheduling and computes the waiting time, turnaround time, and other related metrics for each process.

   - **Key Variables:**
     - `readyQueue`: A queue used to manage processes that are ready for execution.
     - `time`: The current system time, used to simulate the passage of time.
     - `completed`: A counter for the number of completed processes.
     - `totalWaitTime` and `totalTurnAroundTime`: Variables to accumulate total waiting and turnaround times for all processes.
     - `remainingTime`: Array to keep track of the remaining burst time for each process.
     - `isCompleted`: A boolean array to check whether a process is completed.
     - `startTime`, `completionTime`: Arrays to store the start and completion times of each process.

   - **Steps:**
     - Processes that have arrived by the current time are added to the `readyQueue`.
     - The `readyQueue` is sorted by priority, with the process having the highest priority (lowest priority number) at the front.
     - The process at the front of the queue is executed for 1 unit of time.
     - If the process is not completed, it is pushed back into the `readyQueue`.
     - If the process is completed, its completion time, waiting time, and turnaround time are computed.
     - If no processes are ready to execute, the `time` is advanced to the arrival time of the next process.

   - **Average Time Calculations:**
     - After all processes are completed, the function computes the average waiting time and average turnaround time.

   ```cpp
   void findAvgTime(int arrivalTime[], int burstTime[], int priority[], int n) {
       deque<int> readyQueue; 
       int time = 0, completed = 0;
       int totalWaitTime = 0, totalTurnAroundTime = 0;

       vector<int> waitTime(n), turnAroundTime(n), startTime(n, -1), completionTime(n);
       vector<int> remainingTime(burstTime, burstTime + n);  // Track remaining burst time for preemption
       vector<bool> isCompleted(n, false);

       int i = 0; // Index to track unprocessed processes

       while (completed < n) {
           // Add all processes that have arrived by current time
           while (i < n && arrivalTime[i] <= time) {
               readyQueue.push_back(i);
               i++;
           }

           // Sort the ready queue by priority (lower number means higher priority)
           sort(readyQueue.begin(), readyQueue.end(), [&](int a, int b) {
               return priority[a] > priority[b];
           });

           if (!readyQueue.empty()) {
               int current = readyQueue.front();
               readyQueue.pop_front();

               if (startTime[current] == -1) {
                   startTime[current] = time;  // Set start time for the first execution
               }

               // Process one unit of time
               remainingTime[current] -= 1;
               time++;

               // If the process finishes
               if (remainingTime[current] == 0) {
                   completionTime[current] = time;
                   turnAroundTime[current] = completionTime[current] - arrivalTime[current];
                   waitTime[current] = turnAroundTime[current] - burstTime[current];

                   totalWaitTime += waitTime[current];
                   totalTurnAroundTime += turnAroundTime[current];

                   isCompleted[current] = true;
                   completed++;
               }

               // If the process is not completed, push it back to the ready queue
               if (!isCompleted[current] && remainingTime[current] > 0) {
                   readyQueue.push_back(current);
               }
           } else {
               // If no process is ready, advance time to the next arrival
               if (i < n) time = arrivalTime[i];
           }
       }

       // Output process details and average times
       cout << "\nProcess\tArrival Time\tBurst Time\tPriority\tStart Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
       for (int j = 0; j < n; j++) {
           cout << "P" << (j + 1) << "\t\t" << arrivalTime[j] << "\t\t" << burstTime[j] << "\t\t" << priority[j]
                << "\t\t" << startTime[j] << "\t\t" << completionTime[j] << "\t\t" << turnAroundTime[j] << "\t\t" << waitTime[j] << endl;
       }
       cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitTime / n << endl;
       cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnAroundTime / n << endl;
   }
   ```

---

### **Example Walkthrough:**

#### **Input:**
```
Enter the total number of processes: 3
Enter the Arrival time, Burst time, and Priority respectively for Process 1: 0 4 2
Enter the Arrival time, Burst time, and Priority respectively for Process 2: 1 3 1
Enter the Arrival time, Burst time, and Priority respectively for Process 3: 2 2 3
```

#### **Execution:**

1. **Time 0**: Only **P1** has arrived. It starts execution.
   - Remaining Time for **P1** = 3.

2. **Time 1**: **P2** arrives with higher priority (Priority=1).
   - **P1** is preempted. **P2** starts execution.
   - Remaining Time for **P2** = 2.

3. **Time 2**: **P3** arrives with lower priority (Priority=3), but the queue still has **P1** and **P2**.
   - **P2** continues executing.
   - Remaining Time for **P2** = 1.

4. **Time 3**: **P2** completes its execution. **P1** (higher priority than **P3**) is executed next.
   - Remaining Time for **P1** = 2.

5. **Time 4-6**: **P1** completes after executing for 3 more time units. Now, **P3** executes.
   - Remaining Time for **P3** = 1.

6. **Time 7-8**: **P3** completes its execution.

#### **Output:**
```
Process	Arrival Time	Burst Time	Priority	Start Time	Completion Time	Turnaround Time	Waiting Time
P1		0			4			2			0			6			6			2
P2		1			3			1			1			4			3			0
P3		2			2			3			4			8			6			4

Average Waiting Time: 2.00
Average Turnaround Time: 5.00
```

---

### **Viva Questions and Answers:**

1. **What is a preemptive priority CPU scheduling algorithm?**
   - It is a scheduling algorithm where processes are prioritized based on their priority values (lower values mean higher priority). A process can be preempted if a higher priority process arrives.

2. **What happens if two processes have the same priority?**
   - If two processes have the same priority, the algorithm behaves like the **First Come First Serve (FCFS)** algorithm, executing the process that arrived first.

3. **What is the significance of the `remainingTime` array?**
   - The `remainingTime` array tracks the remaining burst time of each process to allow preemption. It is updated every time a process is executed for one unit of time.

4. **What does the `readyQueue` represent?**
   - The `readyQueue` holds processes that have arrived and are ready for execution. The processes are sorted by priority, with the highest priority process (lowest priority number) at the front.

5. **How is the start time of a process determined?**
   - The start time is recorded the first time the process is executed. It is initialized to `-1` and updated when the process begins execution.


