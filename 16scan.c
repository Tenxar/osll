
#include <stdio.h>
#include <stdlib.h>  // For abs function

int no_Track, N, Initial_Head_Pos, No_head_move = 0, direction;

void sort(int arr[], int type, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (type == 1) {
                if (arr[i] > arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            } else {
                if (arr[i] < arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
}

void SCAN(int req_que[]) {
    int right[N], left[N], r = 0, l = 0;

    // Separate the requests into two lists: right and left
    for (int i = 0; i < N; i++) {
        if (req_que[i] > Initial_Head_Pos) {
            right[r++] = req_que[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (req_que[i] < Initial_Head_Pos) {
            left[l++] = req_que[i];
        }
    }

    // Sort both lists
    sort(right, 0, r);  // Sort right side in ascending order
    sort(left, 1, l);   // Sort left side in descending order

    // Now, service requests in the current direction
    if (direction == 0) {  // Moving towards higher tracks
        for (int i = 0; i < r; i++) {
            No_head_move += abs(Initial_Head_Pos - right[i]);
            Initial_Head_Pos = right[i];
            printf("%d ", right[i]);
        }
        direction = 1;  // Reverse direction to lower tracks
    }

    if (direction == 1) {  // Moving towards lower tracks
        for (int i = 0; i < l; i++) {
            No_head_move += abs(Initial_Head_Pos - left[i]);
            Initial_Head_Pos = left[i];
            printf("%d ", left[i]);
        }
    }
}

int main() {
    printf("Enter the Number of tracks on Disk: ");
    scanf("%d", &no_Track);
    printf("Enter the Number of processes requesting to access Disk: ");
    scanf("%d", &N);
    
    int Request_que[N];
    printf("Enter the Request Queue: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &Request_que[i]);
    }

    printf("Enter the initial Head position: ");
    scanf("%d", &Initial_Head_Pos);

    printf("Enter the Direction of Move (0 for higher otherwise 1): ");
    scanf("%d", &direction);

    printf("\n=========================================");
    printf("\n       O U T P U T  ");
    printf("\n SEEK Sequence: ");
    
    SCAN(Request_que);

    printf("\nNumber of Head Moves: %d\n", No_head_move);

    return 0;
}

/*
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_8$ gcc scan.c
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_8$ ./a.out
Enter the Number of tracks on Disk: 200
Enter the Number of processes requesting to access Disk: 8
Enter the Request Queue: 95 180 34 119 11 123 62 64
Enter the initial Head position: 50
Enter the Direction of Move (0 for higher otherwise 1): 0

=========================================
       O U T P U T
 SEEK Sequence: 180 123 119 95 64 62 11 34
Number of Head Moves: 322
*/



RUN:
gcc scan.c -o scan
./scan
