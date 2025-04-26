/*maruf_bro*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

#define ll long long int

#include <stdio.h>

void solve()
{
    int pid[15], bt[15], n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process id of all the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pid[i]);
    }

    printf("Enter burst time of all the processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    int wt[n];
    wt[0] = 0;

    for (int i = 1; i < n; i++)
    {
        wt[i] = bt[i - 1] + wt[i - 1];
    }

    printf("Process ID     Burst Time     Waiting Time     TurnAround Time\n");

    float twt = 0.0, tat = 0.0;
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t", pid[i]);
        printf("%d\t\t", bt[i]);
        printf("%d\t\t", wt[i]);
        printf("%d\t\t\n", bt[i] + wt[i]);

        twt += wt[i];
        tat += bt[i] + wt[i];
    }

    float awt = twt / n;
    float att = tat / n;
    printf("Avg. waiting time= %f\n", awt);
    printf("Avg. turnaround time= %f\n", att);
}

int main()
{
    solve();
    return 0;
}
