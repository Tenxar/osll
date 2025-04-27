#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 100

// Bubble Sort function
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, i;
    int arr[MAX_SIZE];

    // Accept the number of integers and the integers themselves
    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);

    printf("Enter the integers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Fork to create child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("\nChild process (PID: %d) is sorting the array:\n", getpid());

        // Sort the array in the child process
        bubbleSort(arr, n);

        printf("Child sorted array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        exit(0);  // Child exits and becomes a zombie until parent calls wait()
    } else {
        // Parent process
        printf("\nParent process (PID: %d) is sorting the array:\n", getpid());

        // Sort the array in the parent process
        bubbleSort(arr, n);

        printf("Parent sorted array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Delay to observe the zombie state
        printf("\nParent is delaying before calling wait() to demonstrate zombie state.\n");
        sleep(60);  // Check the zombie state with `ps` command during this delay

        // Wait for child process to finish
        wait(NULL);  // This removes the zombie process

        printf("Child process has been cleaned up by wait().\n");
        printf("Parent process finished executing.\n");
    }

    return 0;
}
