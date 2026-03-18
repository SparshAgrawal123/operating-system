#include <stdio.h>

int main() {
    int n, tq, current_time = 0, completed = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    int bt[20], rt[20], at[20], ct[20], tat[20], wt[20], p[20];

    float total_tat = 0, total_wt = 0;

    // 👉 Gantt Chart arrays
    int gantt_p[100], gantt_t[100], g = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
        p[i] = i + 1;
    }

    // Sort by Arrival Time
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                temp = at[j]; at[j] = at[j + 1]; at[j + 1] = temp;
                temp = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = temp;
                temp = rt[j]; rt[j] = rt[j + 1]; rt[j + 1] = temp;
                temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }
        }
    }

    // Round Robin Logic
    while (completed < n) {
        int done_something = 0;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] > 0) {
                done_something = 1;

                // 👉 Store start time
                gantt_p[g] = p[i];
                gantt_t[g++] = current_time;

                if (rt[i] > tq) {
                    current_time += tq;
                    rt[i] -= tq;
                } else {
                    current_time += rt[i];
                    rt[i] = 0;
                    completed++;

                    ct[i] = current_time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    total_tat += tat[i];
                    total_wt += wt[i];
                }
            }
        }

        if (done_something == 0) {
            // 👉 Idle time in Gantt
            gantt_p[g] = -1;
            gantt_t[g++] = current_time;
            current_time++;
        }
    }

    gantt_t[g] = current_time;

    printf("\nP#\tAT\tBT\tCT\tWT\tTAT");
    for (int i = 0; i < n; i++) {
        printf("\n%d\t%d\t%d\t%d\t%d\t%d", p[i], at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\n\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    // 👉 Gantt Chart Output
    printf("\nGantt Chart:\n");

    for (int i = 0; i < g; i++) printf("+-----");
    printf("+\n");

    for (int i = 0; i < g; i++) {
        if (gantt_p[i] == -1)
            printf("| IDL ");
        else
            printf("| P%-2d ", gantt_p[i]);
    }
    printf("|\n");

    for (int i = 0; i < g; i++) printf("+-----");
    printf("+\n");

    for (int i = 0; i <= g; i++) {
        printf("%-6d", gantt_t[i]);
    }
    printf("\n");

    return 0;
}
