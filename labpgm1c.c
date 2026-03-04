#include <stdio.h>
#include <limits.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20], rt[20];
    int i, completed = 0, t = 0, min, shortest = 0, finish_time;
    int check = 0;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);


    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    while (completed != n) {
        min = INT_MAX;
        check = 0;

        for (i = 0; i < n; i++) {
            if ((at[i] <= t) && (rt[i] < min) && rt[i] > 0) {
                min = rt[i];
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        rt[shortest]--;

        if (rt[shortest] == 0) {
            completed++;
            finish_time = t + 1;
            ct[shortest] = finish_time;

            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }


    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }


    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;


    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
