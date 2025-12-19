#include <stdio.h>
#include <stdlib.h>

#define MAX 50

// =====================================================
// FIFO PAGE REPLACEMENT
// =====================================================
void fifo(int pages[], int n, int frames) {
    int memory[MAX], i, j;
    int front = 0, faults = 0;

    for (i = 0; i < frames; i++)
        memory[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n");

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        // Check hit
        for (j = 0; j < frames; j++) {
            if (memory[j] == page) {
                hit = 1;
                break;
            }
        }

        // Page fault
        if (!hit) {
            memory[front] = page;
            front = (front + 1) % frames;
            faults++;
        }

        // Display memory
        printf("Page %d -> [ ", page);
        for (j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }
        printf("] %s\n", hit ? "HIT" : "FAULT");
    }

    printf("Total Page Faults = %d\n", faults);
}

// =====================================================
// LRU PAGE REPLACEMENT
// =====================================================
void lru(int pages[], int n, int frames) {
    int memory[MAX], recent[MAX];
    int i, j, time = 0, faults = 0;

    for (i = 0; i < frames; i++) {
        memory[i] = -1;
        recent[i] = 0;
    }

    printf("\n--- LRU Page Replacement ---\n");

    for (i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        // Check hit
        for (j = 0; j < frames; j++) {
            if (memory[j] == page) {
                hit = 1;
                recent[j] = ++time;
                break;
            }
        }

        // Page fault
        if (!hit) {
            int min = recent[0], pos = 0;

            for (j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    pos = j;
                    break;
                }
                if (recent[j] < min) {
                    min = recent[j];
                    pos = j;
                }
            }

            memory[pos] = page;
            recent[pos] = ++time;
            faults++;
        }

        // Display memory
        printf("Page %d -> [ ", page);
        for (j = 0; j < frames; j++) {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }
        printf("] %s\n", hit ? "HIT" : "FAULT");
    }

    printf("Total Page Faults = %d\n", faults);
}

// =====================================================
// SEGMENTATION SIMULATION
// =====================================================
void segmentation() {
    int memorySize, n, i;
    int segments[MAX];
    int used = 0;

    printf("\nEnter total memory size (KB): ");
    scanf("%d", &memorySize);

    printf("Enter number of segments: ");
    scanf("%d", &n);

    printf("Enter size of each segment:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &segments[i]);

    printf("\n--- Segmentation Allocation ---\n");

    for (i = 0; i < n; i++) {
        printf("Segment %d (%d KB): ", i, segments[i]);
        if (used + segments[i] <= memorySize) {
            printf("Allocated [%d - %d]\n",
                   used, used + segments[i] - 1);
            used += segments[i];
        } else {
            printf("Not Allocated (Insufficient Memory)\n");
        }
    }

    printf("Used Memory = %d KB\n", used);
    printf("Free Memory = %d KB\n", memorySize - used);
}

// =====================================================
// MAIN FUNCTION
// =====================================================
int main() {
    int choice, n, frames, pages[MAX];

    while (1) {
        printf("\n==================================\n");
        printf(" Dynamic Memory Management Visualizer\n");
        printf("==================================\n");
        printf("1. Paging (FIFO)\n");
        printf("2. Paging (LRU)\n");
        printf("3. Segmentation\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Exiting Program...\n");
            break;
        }

        if (choice == 1 || choice == 2) {
            printf("Enter number of pages: ");
            scanf("%d", &n);

            printf("Enter page reference string:\n");
            for (int i = 0; i < n; i++)
                scanf("%d", &pages[i]);

            printf("Enter number of frames: ");
            scanf("%d", &frames);

            if (choice == 1)
                fifo(pages, n, frames);
            else
                lru(pages, n, frames);
        }

        if (choice == 3)
            segmentation();
    }
    return 0;
}

