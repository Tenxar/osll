Can't create, edit, or upload … Not enough storage. Get 30 GB of storage for ₹59.00 ₹15.00/month for 2 months.
#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 50

// Function to find the farthest reference of a page in the future
int findFarthest(int frames[], int frame_size, int page[], int n, int current)
{
    int max_distance = -1;
    int page_to_replace = -1;

    // Find the page that will be used farthest in the future (or not used at all)
    for (int i = 0; i < frame_size; i++) {
        int j;
        for (j = current + 1; j < n; j++) {
            if (frames[i] == page[j]) {
                break;
            }
        }
        // If the page isn't used in the future, select it for replacement
        if (j == n) {
            return i; // Replace this page, as it will not be used again
        }
        // Track the farthest distance
        if (j > max_distance) {
            max_distance = j;
            page_to_replace = i;
        }
    }

    return page_to_replace;
}

// Function to simulate the optimal page replacement algorithm
void optimal(int page[], int n, int frame_size)
{
    if (frame_size < 3) {
        printf("Frame size must be at least 3.\n");
        return;
    }

    int frames[frame_size]; // Array to store pages in memory (frame)
    int page_faults = 0;

    // Initialize the frames to -1 (indicating empty frames)
    for (int i = 0; i < frame_size; i++) {
        frames[i] = -1;
    }

    // Process the page references
    for (int i = 0; i < n; i++) {
        int page_referenced = page[i];
        int page_found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == page_referenced) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            // Page fault occurs, need to replace a page
            page_faults++;

            // If there's space in the frames, insert the page
            int replace_index = -1;
            for (int j = 0; j < frame_size; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    break;
                }
            }

            if (replace_index == -1) {
                // All frames are full, need to replace a page using optimal algorithm
                replace_index = findFarthest(frames, frame_size, page, n, i);
            }

            // Replace the selected page with the new page
            frames[replace_index] = page_referenced;
        }

        // Print the frame contents
        printf("Frames after reference %d: ", page_referenced);
        for (int j = 0; j < frame_size; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    // Print the final results
    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Page Fault Rate: %.2f\n", (float)page_faults / n);
}

int main()
{
    int page_references[MAX_PAGES];
    int n, frame_size;

    // Read input
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &page_references[i]);
    }

    printf("Enter the number of frames (>= 3): ");
    scanf("%d", &frame_size);

    // Run the Optimal Page Replacement Algorithm
    optimal(page_references, n, frame_size);

    return 0;
}

/*
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_6$ gcc optimal.c
shaunty17@DESKTOP-MSSPH5A:/mnt/d/Shounak/New/Assignment_6$ ./a.out
Enter the number of pages: 9
Enter the page reference string: 1 2 3 4 1 2 5 1 2
Enter the number of frames (>= 3): 3
Frames after reference 1: 1 -1 -1
Frames after reference 2: 1 2 -1
Frames after reference 3: 1 2 3
Frames after reference 4: 1 2 4
Frames after reference 1: 1 2 4
Frames after reference 2: 1 2 4
Frames after reference 5: 1 2 5
Frames after reference 1: 1 2 5
Frames after reference 2: 1 2 5

Total Page Faults: 5
Page Fault Rate: 0.56
*/



RUN:
gcc optimal.c -o optimal
./optimal
