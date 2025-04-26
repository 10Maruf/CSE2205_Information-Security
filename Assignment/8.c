#include <stdio.h>

void solve() {
    int i, j, n, a[50], frame[10], no, k, avail, count = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &no);

    for(i = 0; i < no; i++) {
        frame[i] = -1;  // Initialize frames as empty
    }

    j = 0;

    printf("\nRef String\tPage Frames\n");

    for(i = 0; i < n; i++) {
        printf("%d\t\t", a[i]);

        avail = 0;

        // Check if page is already in frame (hit)
        for(k = 0; k < no; k++) {
            if(frame[k] == a[i]) {
                avail = 1;
                break;
            }
        }

        // If not available, it's a page fault
        if(avail == 0) {
            frame[j] = a[i];
            j = (j + 1) % no;  // FIFO rotation
            count++;

            for(k = 0; k < no; k++) {
                if(frame[k] != -1)
                    printf("%d\t", frame[k]);
                else
                    printf("-\t");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", count);
}

int main() {
    solve();
    return 0;
}
