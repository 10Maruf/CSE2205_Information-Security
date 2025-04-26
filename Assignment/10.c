#include <stdio.h>

int n;

// Function to find the page to be replaced (the one that is used the farthest in the future)
int findmax(int a[], int n) {
    int max = a[0];
    int k = 0;

    for (int i = 1; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
            k = i;
        }
    }

    return k;
}

void solve() {
    int seq[30], fr[5], pos[5];
    int flag, m, i, j, k, count = 0, pf = 0;
    int max;

    // Input the sequence length
    printf("Enter maximum limit of the sequence: ");
    scanf("%d", &max);

    // Input the sequence
    printf("\nEnter the sequence: ");
    for (i = 0; i < max; i++) {
        scanf("%d", &seq[i]);
    }

    // Input number of frames
    printf("\nEnter number of frames: ");
    scanf("%d", &n);

    // Initializing the frame and page fault counter
    for (i = 0; i < n; i++) {
        fr[i] = -1; // Empty frame
    }

    // First reference page is added directly to the frame
    fr[0] = seq[0];
    pf++;
    printf("%d\t", fr[0]);

    int count_frames = 1;
    i = 1;

    // Fill in the frames until the count reaches the number of frames
    while (count_frames < n) {
        flag = 1;
        for (j = 0; j < i; j++) {
            if (seq[i] == seq[j]) {
                flag = 0;
                break;
            }
        }

        // If page is not found, insert it into frame
        if (flag != 0) {
            fr[count_frames] = seq[i];
            count_frames++;
            pf++;
            for (k = 0; k < n; k++) {
                printf("%d\t", fr[k]);
            }
        }
        i++;
        printf("\n");
    }

    // Processing the remaining pages in the sequence
    for (i = n; i < max; i++) {
        flag = 1;
        // Check if page already exists in the frames
        for (j = 0; j < n; j++) {
            if (seq[i] == fr[j]) {
                flag = 0;
                break;
            }
        }

        // If the page is not found, replace a page using the OPT algorithm
        if (flag != 0) {
            // Find the position where each page will be used next
            for (j = 0; j < n; j++) {
                m = fr[j];
                for (k = i; k < max; k++) {
                    if (seq[k] == m) {
                        pos[j] = k;
                        break;
                    } else {
                        pos[j] = max + 1;
                    }
                }
            }

            // Find the page with the maximum future usage (to replace it)
            int replace_index = findmax(pos, n);

            // Replace the page and display the new frame contents
            fr[replace_index] = seq[i];
            pf++;
            for (k = 0; k < n; k++) {
                printf("%d\t", fr[k]);
            }
        }
        printf("\n");
    }

    // Calculate and display page fault rate
    float pfr = (float)pf / (float)max;
    printf("\nThe number of page faults are: %d", pf);
    printf("\nPage fault rate: %f", pfr);
}

int main() {
    solve();
    return 0;
}
