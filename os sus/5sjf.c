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

/*
IMplement the c program for for cpu scheduling algorithm sjf preemptive and round robing with different arrival time 

what is thread?
    1.) Lightweight Process: A thread is the smallest unit of execution within a process. Unlike processes, threads share the same memory space and resources, making them more efficient to create and manage.

    1.) Shared Resources: Threads within the same process share code, data, and system resources, allowing for faster communication and coordination compared to separate processes.

    1.) Parallel Execution: Threads enable multitasking by allowing multiple threads to run concurrently (on multi-core CPUs) or via time-slicing (on single-core CPUs), improving performance in applications like web servers and multimedia software.

    1.) Independent Execution Paths: Each thread has its own stack, program counter, and register state, allowing it to perform different tasks independently while still belonging to the same process.

   Type of threads?
   User-Level Threads (ULT)

    Threads are managed by user programs (not the OS kernel).

    Very fast to create and switch.

    But if one thread blocks (stops), all threads in that process block.

    Example: old libraries like pthread can run in user mode.

Kernel-Level Threads (KLT)

    Threads are managed by the OS kernel directly.

    Kernel knows about each thread and can schedule them individually.

    Slower than user threads (more overhead), but if one thread blocks, others can still run.

    Example: Windows, Linux handle kernel threads.

Hybrid Threads

    Mix of User and Kernel threads.

    User manages threads first, but kernel helps when needed.

    Tries to get the speed of User threads and the power of Kernel threads together.

    Example: Solaris OS, modern systems.


    Q) Thread Control Block (TCB):

    A TCB is a data structure maintained by the OS for each thread, storing critical execution details such as:

        Thread ID (unique identifier)

        Program Counter (current instruction)

        Register States (CPU registers' values)

        Stack Pointer (thread-specific stack)

        Scheduling Info (priority, state: ready/running/blocked)

        Pointer to the Process’s PCB (since threads share the same process resources).


        what is PSOIX?
        Standard API for Threading: Pthreads is a POSIX-standard (IEEE 1003.1c) library used for creating and managing threads in Unix-like systems (Linux, macOS). It provides functions like pthread_create(), pthread_join(), and pthread_mutex_lock() for thread operations.

        Q) it;s function?

        pthread_create() 

    
            pthread_create() is a POSIX function used to create a new thread.

            It starts a new thread that runs a specific function you provide.

            After calling pthread_create(), two threads will run at the same time — the main thread and the new thread.

        pthread_exit()

            It is a POSIX thread function used to terminate the calling thread safely.

            It allows the thread to finish execution and optionally return a value to other threads.

        pthread_join()

            It is a POSIX thread function used by one thread to wait for another thread to terminate.

            It helps in synchronization, making sure that a thread finishes before the next action continues.



   SJF Preemptive Algorithm (Simple Steps):sjf

    Start at time = 0.

    Check all processes that have arrived.

    Pick the process with the smallest remaining burst time.

    Run it for 1 unit of time.

    After 1 unit, again check if any new process has arrived with smaller burst time.

    If yes, switch to that new process (preempt).

    Repeat steps 3-6 until all processes are finished.



    Round Robin Algorithm (Simple Steps):

    Start at time = 0.

    Put all processes in a queue (like a line).

    Pick the first process from the queue.

    Run it for a fixed time called Time Quantum (example: 4ms).

    If the process finishes before time quantum, remove it from the queue.

    If it does not finish, pause it and put it at the end of the queue.

    Pick the next process and repeat steps 4–6.

    Continue until all processes are finished.

*/
