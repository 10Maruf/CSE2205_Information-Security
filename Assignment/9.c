#include <stdio.h>

void solve() {
    int i, j, k, min, rs[25], m[10], count[10], flag[25], n, f, pf = 0, next = 1;

    // Input the length of the reference string
    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    // Input the reference string
    printf("Enter the reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
        flag[i] = 0;
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    // Initialize the frames and the count for each frame
    for(i = 0; i < f; i++) {
        count[i] = 0;
        m[i] = -1;
    }

    // Page replacement process
    printf("\nThe Page Replacement process is:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < f; j++) {
            if(m[j] == rs[i]) {
                // If page is found in the frame (hit)
                flag[i] = 1;
                count[j] = next;
                next++;
            }
        }

        if(flag[i] == 0) {
            // If the page is not found in the frame (miss)
            if(i < f) {
                m[i] = rs[i];
                count[i] = next;
                next++;
            } else {
                // Find the least recently used page
                min = 0;
                for(j = 1; j < f; j++) {
                    if(count[min] > count[j]) {
                        min = j;
                    }
                }

                // Replace the least recently used page
                m[min] = rs[i];
                count[min] = next;
                next++;
            }
            pf++; // Increment page fault count
        }

        // Print the frame content after each reference
        for(j = 0; j < f; j++) {
            printf("%d\t", m[j]);
        }

        if(flag[i] == 0) {
            printf("PF No. -- %d", pf);
        }
        printf("\n");
    }

    // Output the total number of page faults
    printf("\nThe number of page faults using LRU are %d\n", pf);
}

int main() {
    solve();
    return 0;
}
