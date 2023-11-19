#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

void displayFrames(int frames[], int frameSize) {
    for (int i = 0; i < frameSize; ++i) {
        if (frames[i] == -1)
            printf("Empty ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

int findLRU(int time[], int n) {
    int minimum = time[0], pos = 0;

    for (int i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}

void optimalPageReplace(int pages[], int n) {
    int frames[MAX_FRAMES], page_faults = 0, index = 0;
    bool isPresent = false;

    for (int i = 0; i < MAX_FRAMES; ++i)
        frames[i] = -1;

    for (int i = 0; i < n; ++i) {
        isPresent = false;
        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j] == pages[i]) {
                isPresent = true;
                break;
            }
        }

        if (!isPresent) {
            if (frames[index] != -1) {
                int temp[MAX_FRAMES];
                for (int j = 0; j < MAX_FRAMES; ++j) {
                    bool flag = false;
                    for (int k = i + 1; k < n; ++k) {
                        if (pages[k] == frames[j]) {
                            temp[j] = k;
                            flag = true;
                            break;
                        }
                    }
                    if (!flag)
                        temp[j] = n + 1;
                }
                int farthest = 0;
                for (int j = 1; j < MAX_FRAMES; ++j) {
                    if (temp[j] > temp[farthest])
                        farthest = j;
                }
                index = farthest;
            }
            frames[index] = pages[i];
            index = (index + 1) % MAX_FRAMES;
            page_faults++;
        }

        printf("Frames after page %d: ", pages[i]);
        displayFrames(frames, MAX_FRAMES);
    }

    printf("\nTotal Page Faults (Optimal): %d\n", page_faults);
}

void lruPageReplace(int pages[], int n) {
    int frames[MAX_FRAMES], page_faults = 0;
    int index[MAX_FRAMES];

    for (int i = 0; i < MAX_FRAMES; ++i) {
        frames[i] = -1;
        index[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        bool isPresent = false;

        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j] == pages[i]) {
                isPresent = true;
                index[j] = i;
                break;
            }
        }

        if (!isPresent) {
            int leastUsed = findLRU(index, MAX_FRAMES);
            frames[leastUsed] = pages[i];
            index[leastUsed] = i;
            page_faults++;
        }

        printf("Frames after page %d: ", pages[i]);
        displayFrames(frames, MAX_FRAMES);
    }

    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}

void fcfsPageReplace(int pages[], int n) {
    int frames[MAX_FRAMES], page_faults = 0, frameIndex = 0;

    for (int i = 0; i < MAX_FRAMES; ++i)
        frames[i] = -1;

    for (int i = 0; i < n; ++i) {
        bool isPresent = false;

        for (int j = 0; j < MAX_FRAMES; ++j) {
            if (frames[j] == pages[i]) {
                isPresent = true;
                break;
            }
        }

        if (!isPresent) {
            frames[frameIndex] = pages[i];
            frameIndex = (frameIndex + 1) % MAX_FRAMES;
            page_faults++;
        }

        printf("Frames after page %d: ", pages[i]);
        displayFrames(frames, MAX_FRAMES);
    }

    printf("\nTotal Page Faults (FCFS): %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);

    printf("Page reference string: ");
    for (int i = 0; i < n; ++i)
        printf("%d ", pages[i]);
    printf("\n\n");

    fcfsPageReplace(pages, n);
    lruPageReplace(pages, n);
    optimalPageReplace(pages, n);

    return 0;
}