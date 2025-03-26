#include <stdio.h>

void printProcess(int processSize[], int processes, int allocation[]) {
    printf("\n| Process No. | Process Size | Block No. |\n");
    for (int i = 0; i < processes; i++) {
        printf("|%13d|%14d|", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%13d|\n", allocation[i] + 1);
        else
            printf("Not Allocated|\n");
    }
}

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] = -1;
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation");
    printProcess(processSize, processes, allocation);
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i] && (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])) {
                bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] = -1;
        }
    }
    printf("\nBest Fit Allocation");
    printProcess(processSize, processes, allocation);
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i] && (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])) {
                worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] = -1;
        }
    }
    printf("\nWorst Fit Allocation");
    printProcess(processSize, processes, allocation);
}

int main() {
    int blocks, processes, choice;
    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    int blockSize[blocks], originalBlockSize[blocks];
    printf("Enter sizes of %d memory blocks: ", blocks);
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &blockSize[i]);
        originalBlockSize[i] = blockSize[i];
    }
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    int processSize[processes];
    printf("Enter sizes of %d processes: ", processes);
    for (int i = 0; i < processes; i++) {
        scanf("%d", &processSize[i]);
    }
    do {
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                firstFit(blockSize, blocks, processSize, processes);
                break;
            case 2:
                bestFit(blockSize, blocks, processSize, processes);
                break;
            case 3:
                worstFit(blockSize, blocks, processSize, processes);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        for (int i = 0; i < blocks; i++) {
            blockSize[i] = originalBlockSize[i];
        }
    } while (choice != 4);
    printf("\n");
    return 0;
}
