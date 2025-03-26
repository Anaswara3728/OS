#include <stdio.h>
#include <stdbool.h>

// Function to check if a page exists in the frame
bool isPresent(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return true;
    }
    return false;
}

// FIFO 
int FIFO(int pages[], int n, int frames[], int fCount) {
    int pageFaults = 0, index = 0;
    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, fCount, pages[i])) {
            frames[index] = pages[i];
            index = (index + 1) % fCount;
            pageFaults++;
        }
    }
    return pageFaults;
}

// Optimal Page Replacement
int findOptimal(int pages[], int frames[], int fCount, int index, int n) {
    int farthest = -1, replaceIndex = -1;
    for (int i = 0; i < fCount; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }
        if (j == n) return i; // If never used again, replace this frame
    }
    return replaceIndex;
}

int Optimal(int pages[], int n, int frames[], int fcount) {
    int pageFaults = 0;
    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, fcount, pages[i])) {
            if (i < fcount) frames[i] = pages[i];
            else frames[findOptimal(pages, frames, fcount, i, n)] = pages[i];
            pageFaults++;
        }
    }
    return pageFaults;
}

// LRU Page Replacement
int findLRU(int pages[], int frames[], int fcount, int index) {
    int leastRecent = index, replaceIndex = -1;
    for (int i = 0; i < fcount; i++) {
        for (int j = index - 1; j >= 0; j--) {
            if (frames[i] == pages[j]) {
                if (j < leastRecent) {
                    leastRecent = j;
                    replaceIndex = i;
                }
                break;
            }
        }
    }
    return replaceIndex;
}

int LRU(int pages[], int n, int frames[], int fcount) {
    int pageFaults = 0;
    for (int i = 0; i < n; i++) {
        if (!isPresent(frames, fcount, pages[i])) {
            if (i < fcount) frames[i] = pages[i];
            else frames[findLRU(pages, frames, fcount, i)] = pages[i];
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int n, fcount;
    printf("Enter the no. of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the reference sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter the no. of frames: ");
    scanf("%d", &fcount);
    int frames[fcount];
    for (int i = 0; i < fcount; i++) frames[i] = -1;

    printf("\nPage Faults (FIFO): %d\n", FIFO(pages, n, frames, fcount));
    for (int i = 0; i < fcount; i++) frames[i] = -1; // Reset frames
    printf("Page Faults (OPT): %d\n", Optimal(pages, n, frames, fcount));
    for (int i = 0; i < fcount; i++) frames[i] = -1; // Reset frames
    printf("Page Faults (LRU): %d\n", LRU(pages, n, frames, fcount));
    
    return 0;
}
