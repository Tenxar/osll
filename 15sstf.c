
#include <stdio.h>
#include <stdlib.h>  // For abs()
#include <limits.h>  // For INT_MAX

int no_Track, N, Initial_Head_Pos, No_head_move = 0;

int min_index(int req_que[], int visited[])
{
    int min = INT_MAX, index = -1;
    for (int i = 0; i < N; i++){
        if (!visited[i] && abs(Initial_Head_Pos - req_que[i]) < min)
        {
            min = abs(Initial_Head_Pos - req_que[i]);
            index = i;
        }
    }
    return index;
}

void SSTF(int request_que[], int visited[])
{
    int min_Index;
    for (int i = 0; i < N; i++)
    {
        min_Index = min_index(request_que, visited);
        visited[min_Index] = 1;  // Mark this request as visited
        printf("\t%d", request_que[min_Index]);
        
        // Calculate the head movement as the absolute difference between the current head position and the selected request
        No_head_move += abs(Initial_Head_Pos - request_que[min_Index]);
        
        // Update the head position to the newly selected request position
        Initial_Head_Pos = request_que[min_Index];
    }
}

int main()
{
    printf("Enter the Number of tracks on Disk: ");
    scanf("%d", &no_Track);

    printf("Enter the Number of requests to access Disk: ");
    scanf("%d", &N);
    
    int Request_que[N];
    printf("Enter the Request Queue: ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &Request_que[i]);
    }

    printf("Enter the initial Head position: ");
    scanf("%d", &Initial_Head_Pos);

    int Visited[N];
    for (int i = 0; i < N; i++)
        Visited[i] = 0;  // Initialize all requests as unvisited

    printf("\n=========================================");
    printf("\n       O U T P U T  ");
    printf("\n SEEK Sequence:");
    SSTF(Request_que, Visited);
    printf("\n Number of Head Moves: %d\n", No_head_move);

    return 0;
}

/*
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_8$ gcc sstf.c
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_8$ ./a.out
Enter the Number of tracks on Disk: 200
Enter the Number of requests to access Disk: 8
Enter the Request Queue: 100 50 25 75 125 150 190 69
Enter the initial Head position: 30

=========================================
       O U T P U T
 SEEK Sequence: 25      50      69      75      100     125     150     190
 Number of Head Moves: 170
*/



RUN:
gcc -o sstf sstf.c
./sstf
