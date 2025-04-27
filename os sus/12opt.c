#include<stdio.h>

int main() {
    int frames_number, page_faults, pages_number, frames[10], pages[30], temp[10], flag1, flag2, flag3, i, j, k, pos, max;
    
    printf("Enter number of frames: ");
    scanf("%d", &frames_number);
    
    printf("Enter number of pages: ");
    scanf("%d", &pages_number);
    
    printf("Enter page reference string: ");
    for(i = 0; i < pages_number; ++i) {
        scanf("%d", &pages[i]);
    }

    // Initialize frames to -1 (empty)
    for(i = 0; i < frames_number; ++i) {
        frames[i] = -1;
    }

    page_faults = 0; // Initialize the page fault count

    // Iterate through each page in the reference string
    for(i = 0; i < pages_number; ++i) {
        flag1 = flag2 = 0; // Reset flags for each page

        // Check if the page is already in one of the frames
        for(j = 0; j < frames_number; ++j) {
            if(frames[j] == pages[i]) {
                flag1 = flag2 = 1;
                break;
            }
        }

        // If the page is not found in the frames, we have a page fault
        if(flag1 == 0) {
            // Try to place the page in an empty frame
            for(j = 0; j < frames_number; ++j) {
                if(frames[j] == -1) {
                    frames[j] = pages[i];
                    page_faults++;
                    flag2 = 1;
                    break;
                }
            }
        }

        // If the page is not found and there are no empty frames, we need to replace a page
        if(flag2 == 0) {
            flag3 = 0;
            // Calculate the next use of each page in the frames
            for(j = 0; j < frames_number; ++j) {
                temp[j] = -1;
                for(k = i + 1; k < pages_number; ++k) {
                    if(frames[j] == pages[k]) {
                        temp[j] = k;
                        break;
                    }
                }
            }

            // Find a page that is not used in the future (temp[j] == -1)
            for(j = 0; j < frames_number; ++j) {
                if(temp[j] == -1) {
                    pos = j;
                    flag3 = 1;
                    break;
                }
            }

            // If all pages are used in the future, replace the one with the farthest future use
            if(flag3 == 0) {
                max = temp[0];
                pos = 0;
                for(j = 1; j < frames_number; ++j) {
                    if(temp[j] > max) {
                        max = temp[j];
                        pos = j;
                    }
                }
            }

            frames[pos] = pages[i];
            page_faults++;
        }

        // Print the current state of the frames
        printf("\n");
        for(j = 0; j < frames_number; ++j) {
            printf("%d\t", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", page_faults);
    return 0;
}

