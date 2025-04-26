#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int resources[MAX_RESOURCES];
int work[MAX_RESOURCES];
int marked[MAX_PROCESSES];

int main() {
    int num_processes, num_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    // Input total resources
    for (int i = 0; i < num_resources; i++) {
        printf("Enter total amount of Resource R%d: ", i + 1);
        scanf("%d", &resources[i]);
    }

    // Input request matrix
    printf("Enter the Request Matrix (%dx%d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter the Allocation Matrix (%dx%d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Initialize available resources
    for (int j = 0; j < num_resources; j++) {
        available[j] = resources[j];
        for (int i = 0; i < num_processes; i++) {
            available[j] -= allocation[i][j];
        }
    }

    // Initialize marked array
    for (int i = 0; i < num_processes; i++) {
        marked[i] = 0;
    }

    // Mark processes with zero allocation
    for (int i = 0; i < num_processes; i++) {
        int all_zero = 1;
        for (int j = 0; j < num_resources; j++) {
            if (allocation[i][j] != 0) {
                all_zero = 0;
                break;
            }
        }
        if (all_zero) {
            marked[i] = 1;
        }
    }

    // Initialize work = available
    for (int j = 0; j < num_resources; j++) {
        work[j] = available[j];
    }

    // Process request <= work logic
    int progress;
    do {
        progress = 0;
        for (int i = 0; i < num_processes; i++) {
            if (marked[i] == 0) {
                int can_be_processed = 1;
                for (int j = 0; j < num_resources; j++) {
                    if (request[i][j] > work[j]) {
                        can_be_processed = 0;
                        break;
                    }
                }
                if (can_be_processed) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    marked[i] = 1;
                    progress = 1;
                }
            }
        }
    } while (progress);

    // Final deadlock check
    int deadlock = 0;
    printf("\nProcesses in deadlock (if any):\n");
    for (int i = 0; i < num_processes; i++) {
        if (marked[i] == 0) {
            printf("Process %d\n", i);
            deadlock = 1;
        }
    }

    if (!deadlock) {
        printf("No deadlock detected.\n");
    } else {
        printf("Deadlock detected!\n");
    }

    return 0;
}
