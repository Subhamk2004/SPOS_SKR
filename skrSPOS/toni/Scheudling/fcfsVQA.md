### **Code Explanation:**

This C++ program simulates the **First Come First Serve (FCFS)** CPU scheduling algorithm, which is one of the simplest CPU scheduling algorithms. It calculates important metrics related to process scheduling like waiting time, turnaround time, and also visualizes the scheduling using a **Gantt chart**.

#### **Key Concepts:**

1. **Arrival Time (AT)**: The time when a process arrives in the ready queue.
2. **Burst Time (BT)**: The time required by the process for execution on the CPU.
3. **Completion Time (CT)**: The time when a process finishes its execution.
4. **Turnaround Time (TAT)**: The total time a process takes from arrival to completion (TAT = CT - AT).
5. **Waiting Time (WT)**: The time a process spends waiting in the ready queue before it gets executed (WT = TAT - BT).

The **FCFS algorithm** schedules processes in the order of their arrival time. Processes that arrive earlier get executed first. If two processes have the same arrival time, they are executed in the order of their arrival in the input list.

---

### **Functions:**

#### 1. **`findCompletionTime`**:
   This function calculates the **Completion Time (CT)** for each process, as well as the **Start Time (ST)** for each process.

   - The start time of the first process is equal to its arrival time (`at[0]`).
   - For each subsequent process, the start time is the maximum of the completion time of the previous process and the arrival time of the current process.
   - The completion time is calculated as the start time plus the burst time.

   ```cpp
   void findCompletionTime(int n, int at[], int bt[], int completion[], int start[]) {
       completion[0] = at[0] + bt[0];
       start[0] = at[0];
       
       for(int i = 1; i < n; i++) {
           start[i] = max(completion[i-1], at[i]);
           completion[i] = start[i] + bt[i];
       }
   }
   ```

#### 2. **`findTurnAroundTime`**:
   This function calculates the **Turnaround Time (TAT)** for each process. It is calculated as the difference between the completion time and the arrival time.

   ```cpp
   void findTurnAroundTime(int n, int at[], int completion[], int tat[]) {
       for(int i = 0; i < n; i++) {
           tat[i] = completion[i] - at[i];
       }
   }
   ```

#### 3. **`findWaitingTime`**:
   This function calculates the **Waiting Time (WT)** for each process. It is calculated as the difference between the turnaround time and the burst time.

   ```cpp
   void findWaitingTime(int n, int at[], int bt[], int completion[], int wt[]) {
       for(int i = 0; i < n; i++) {
           wt[i] = completion[i] - at[i] - bt[i];
       }
   }
   ```

#### 4. **`printGanttChart`**:
   This function prints a **Gantt Chart** to visualize the execution order of processes along with their start and end times.

   ```cpp
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
   ```

#### 5. **`findAvgTime`**:
   This function is the main driver of the program. It calls other functions to calculate completion time, turnaround time, and waiting time, then prints the results and averages for these metrics. Additionally, it displays the Gantt chart.

   ```cpp
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
   ```

---

### **Main Function:**
The `main` function takes user input for the number of processes, their arrival times, and burst times, and then calls `findAvgTime` to simulate the scheduling and calculate the necessary metrics.

```cpp
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
```

---

### **Example Walkthrough:**

#### **Input:**
```
Enter the number of processes: 4
Enter the Arrival Time and Burst Time of process 1: 0 4
Enter the Arrival Time and Burst Time of process 2: 1 3
Enter the Arrival Time and Burst Time of process 3: 2 5
Enter the Arrival Time and Burst Time of process 4: 3 2
```

#### **Execution:**

1. **Process 1 (P1)**: Arrives at 0, executes for 4 units.
   - Start time = 0, Completion time = 4.
   
2. **Process 2 (P2)**: Arrives at 1, executes for 3 units after P1.
   - Start time = 4, Completion time = 7.

3. **Process 3 (P3)**: Arrives at 2, executes for 5 units after P2.
   - Start time = 7, Completion time = 12.

4. **Process 4 (P4)**: Arrives at 3, executes for 2 units after P3.
   - Start time = 12, Completion time = 14.

#### **Output:**
```
Process No. Arrival Time Burst Time Start Time Completion Time Wait Time Turnaround Time
1           0           4            0           4             0            4
2           1           3            4           7             3            6
3           2           5            7           12            5            10
4           3           2            12          14            9            11

Average Waiting Time: 4.25
Average Turnaround Time: 7.75

Gantt Chart:
-------------------------------------------------
|  P1  |  P2  |  P3  |  P4  |
-------------------------------------------------
0______4______7______12______14
```

---

### **Viva Questions and Answers:**

1. **What is the First Come First Serve (FCFS) scheduling algorithm?**
   - FCFS is a simple scheduling algorithm where processes are executed in the order they arrive in the ready queue.

2. **How are Completion Time and Turnaround Time calculated?**
   - Completion Time is calculated by adding the burst time to the start time of a process. Turnaround Time is the difference between the completion time and the arrival time.

3. **How does the program calculate Waiting Time?**
   - Waiting Time is calculated as the difference between the turnaround time and the burst time of a process.

4. **What is the significance of the Gantt Chart in CPU scheduling?**
   - The Gantt Chart visually shows the order of execution of processes, helping in understanding how time is allocated to each process.

5. **What are the advantages and limitations of FCFS?**
   - **Advantages**: Simple to implement and easy to understand.
   - **Limitations**: It can lead to the "convoy effect," where short processes are delayed by long processes, leading to high average waiting times.
