#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], at[20], ct[20];
    int pid[20], completed[20];
    int i, j, time = 0, min_index;
    float twt = 0.0, ttat = 0.0, awt, att;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        completed[i] = 0;

        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    int count = 0;

    while (count < n) {
        int min = 9999;
        min_index = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && completed[i] == 0) {
                if (bt[i] < min) {
                    min = bt[i];
                    min_index = i;
                }
            }
        }

        if (min_index == -1) {
            time++;
        } else {
            ct[min_index] = time + bt[min_index];
            wt[min_index] = time - at[min_index];
            if (wt[min_index] < 0)
                wt[min_index] = 0;

            tat[min_index] = bt[min_index] + wt[min_index];

            time = ct[min_index];
            completed[min_index] = 1;
            count++;
        }
    }

    // Calculate averages
    for (i = 0; i < n; i++) {
        twt += wt[i];
        ttat += tat[i];
    }

    awt = twt / n;
    att = ttat / n;

    // Output
    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f\n", att);

    return 0;
}
