#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n;

    // Input number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    // Input elements
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) { // Child process
        // Sorting in child process
        printf("Child process (PID: %d) sorting...\n", getpid());
        bubbleSort(arr, n);
        printf("Sorted array by child process: ");
        printArray(arr, n);

        // Simulate orphan state by making the child sleep
        printf("Child process going to sleep to become an orphan...\n");
        sleep(5);
        printf("Child process (orphan) finished execution.\n");

    } else { // Parent process
        // Sorting in parent process
        printf("Parent process (PID: %d) sorting...\n", getpid());
        bubbleSort(arr, n);
        printf("Sorted array by parent process: ");
        printArray(arr, n);

        // Wait for the child to complete
        wait(NULL);
        printf("Parent process finished.\n");
    }

    return 0;
}
