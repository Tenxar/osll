#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
};

void calculateTimes(struct Process processes[], int n) {
    int completed = 0, currentTime = 0;

    while (completed != n) {
        int shortest = -1;
        int minRemainingTime = INT_MAX;

        // Find the process with the shortest remaining time at currentTime
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime &&
                processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minRemainingTime) {

                minRemainingTime = processes[i].remainingTime;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;  // No process ready; increment time
            continue;
        }

        // Process the shortest job for one unit of time
        processes[shortest].remainingTime--;
        currentTime++;

        // If the process completes
        if (processes[shortest].remainingTime == 0) {
            completed++;
            processes[shortest].completionTime = currentTime;
            processes[shortest].turnaroundTime = processes[shortest].completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnaroundTime - processes[shortest].burstTime;
        }
    }
}

void printResults(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
    }

    calculateTimes(processes, n);
    printResults(processes, n);

    return 0;
}
