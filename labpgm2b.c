#include <stdio.h>

int main() {
    int n, i, j, pos;
    int at[10], bt[10], pr[10];
    int ct[10], tat[10], wt[10];
    int time = 0, completed = 0, min;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    int done[10] = {0};

    while(completed < n) {
        min = 999;
        pos = -1;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && done[i] == 0 && pr[i] < min) {
                min = pr[i];
                pos = i;
            }
        }

        if(pos == -1) {
            time++;
        }
        else {
            time += bt[pos];
            ct[pos] = time;
            done[pos] = 1;
            completed++;
        }
    }

    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    printf("\nPID\tAT\tBT\tPR\tTAT\tWT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], pr[i], tat[i], wt[i]);
    }

    return 0;
}
