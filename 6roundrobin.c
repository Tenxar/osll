
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

// Process control block structure
typedef struct {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time (execution time)
    int remaining_time; // Remaining burst time
    int start_time;     // Start time for completion calculation
    int completion_time; // Completion time
    int waiting_time;   // Waiting time
    int turnaround_time; // Turnaround time
} Process;

// Function to calculate waiting time and turnaround time
void calculate_waiting_turnaround(Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }
    
    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);
}

// Round Robin Scheduling Algorithm
void round_robin(Process proc[], int n, int time_quantum) {
    int time = 0; // Current time in the simulation
    int completed = 0; // Count of completed processes
    int front = 0, rear = 0; // Queue pointers
    int queue[MAX];
    
    // Initialize queue with -1 indicating empty
    for (int i = 0; i < MAX; i++) {
        queue[i] = -1;
    }
    
    // Add processes to the ready queue based on arrival time
    while (completed < n) {
        // Check if a process has arrived and is ready to be added to the queue
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time && proc[i].remaining_time > 0 && queue[rear] != i) {
                queue[rear] = i;
                rear = (rear + 1) % MAX;
            }
        }
        
        // If there are no ready processes in the queue, just increment time
        if (queue[front] == -1) {
            time++;
            continue;
        }
        
        // Get the process ID at the front of the queue
        int current_pid = queue[front];
        front = (front + 1) % MAX;  // Move front to the next process in the queue
        
        // If the process has not been completed yet
        if (proc[current_pid].remaining_time > 0) {
            int time_slice = (proc[current_pid].remaining_time <= time_quantum) ? proc[current_pid].remaining_time : time_quantum;
            
            // Update the time and the remaining time of the process
            time += time_slice;
            proc[current_pid].remaining_time -= time_slice;
            
            // If process is completed, set its completion time
            if (proc[current_pid].remaining_time == 0) {
                proc[current_pid].completion_time = time;
                completed++;
            }
        }
        
        // Re-enqueue the process if it is not finished
        if (proc[current_pid].remaining_time > 0) {
            queue[rear] = current_pid;
            rear = (rear + 1) % MAX;
        }
    }
    
    // Calculate waiting time and turnaround time
    calculate_waiting_turnaround(proc, n);
}

// Main function
int main() {
    int n, time_quantum;
    
    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process proc[n];
    
    // Input process details (PID, arrival time, burst time)
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("\nEnter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;  // Initialize remaining time
        proc[i].start_time = -1;  // Initially, start time is undefined
    }
    
    // Input time quantum
    printf("\nEnter the time quantum: ");
    scanf("%d", &time_quantum);
    
    // Sort processes based on arrival time (non-decreasing)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    
    // Run the Round Robin scheduling algorithm
    round_robin(proc, n, time_quantum);
    
    // Display results
    printf("\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, 
               proc[i].arrival_time, 
               proc[i].burst_time, 
               proc[i].completion_time, 
               proc[i].waiting_time, 
               proc[i].turnaround_time);
    }
    
    return 0;
}

/*
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_3$ gcc Assignment_3_B.c
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_3$ ./a.out
Enter the number of processes: 3

Enter arrival time and burst time for Process 1: 0 5

Enter arrival time and burst time for Process 2: 1 4

Enter arrival time and burst time for Process 3: 2 3

Enter the time quantum: 2

Average Waiting Time = 4.33
Average Turnaround Time = 8.33

PID     Arrival Time    Burst Time      Completion Time Waiting Time    Turnaround Time
1       0               5               5               0               5
2       1               4               11              6               10
3       2               3               12              7               10
*/


/*
RUN:
gcc round_robin.c -o round_robin
./round_robin
*/