#include <stdio.h>

int main() {
    int p, r; // p = number of processes, r = number of resources
    int alloc[5][3], max[5][3], need[5][3], avail[3];
    int safeSeq[5], finished[5] = {0}, count = 0;

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &p, &r);

    printf("Enter Allocation Matrix (%dx%d):\n", p, r);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix (%dx%d):\n", p, r);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources (%d): ", r);
    for (int i = 0; i < r; i++)
        scanf("%d", &avail[i]);

    // Calculate need matrix
    printf("\nNeed Matrix:\n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    // Find safe sequence
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!finished[i]) {
                int canAllocate = 1;
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < r; j++)
                        avail[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finished[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return 1;
        }
    }

    // If safe sequence found
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    printf("Available resources after completion: ");
    for (int i = 0; i < r; i++) {
        printf("%d ", avail[i]);
    }
    printf("\n");

    return 0;
}
