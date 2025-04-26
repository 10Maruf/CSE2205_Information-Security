#include <stdio.h>

void displayFrames(int frames[], int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

int findOptimal(int frames[], int frameCount, int pages[], int pageCount, int currentIndex) {
    int farthest = currentIndex, index = -1;
    for (int i = 0; i < frameCount; i++) {
        int j;
        for (j = currentIndex; j < pageCount; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == pageCount) // If a frame is never used again
            return i;
    }
    return (index == -1) ? 0 : index;
}

void optimalPageReplacement(int pages[], int pageCount, int frameCount) {
    int frames[frameCount];
    for (int i = 0; i < frameCount; i++)
        frames[i] = -1;

    int pageFaults = 0;

    printf("Page Reference String | Frames\n");
    printf("-----------------------|-----------------\n");

    for (int i = 0; i < pageCount; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int replaceIndex;
            if (i < frameCount) {
                replaceIndex = i; // Fill empty frames first
            } else {
                replaceIndex = findOptimal(frames, frameCount, pages, pageCount, i + 1);
            }
            frames[replaceIndex] = page;
            pageFaults++;
        }

        printf("         %d            |", page);
        displayFrames(frames, frameCount);
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pageCount, frameCount;

    printf("Enter the number of pages: ");
    scanf("%d", &pageCount);

    int pages[pageCount];
    printf("Enter the page reference string: ");
    for (int i = 0; i < pageCount; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frameCount);

    optimalPageReplacement(pages, pageCount, frameCount);

    return 0;
}