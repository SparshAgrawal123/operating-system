#include <stdio.h>
struct Process {
    int pid, at, bt, type, ct, tat, wt, start;
};
void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n], systemQ[n], userQ[n];
    int sysCount = 0, userCount = 0;
    for(int i = 0; i < n; i++) {
        printf("\nProcess%d Arrival Time and Burst Time:\n", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].pid = i + 1;
        printf("Type (0=System, 1=User): ");
        scanf("%d", &p[i].type);
        if(p[i].type == 0)
            systemQ[sysCount++] = p[i];
        else
            userQ[userCount++] = p[i];
    }
    sortByArrival(systemQ, sysCount);
    sortByArrival(userQ, userCount);
    int time = 0;
    for(int i = 0; i < sysCount; i++) {
        if(time < systemQ[i].at)
            time = systemQ[i].at;
        systemQ[i].start = time;
        time += systemQ[i].bt;
        systemQ[i].ct = time;
        systemQ[i].tat = systemQ[i].ct - systemQ[i].at;
        systemQ[i].wt = systemQ[i].tat - systemQ[i].bt;
    }
    for(int i = 0; i < userCount; i++) {
        if(time < userQ[i].at)
            time = userQ[i].at;
        userQ[i].start = time;
        time += userQ[i].bt;
        userQ[i].ct = time;
        userQ[i].tat = userQ[i].ct - userQ[i].at;
        userQ[i].wt = userQ[i].tat - userQ[i].bt;
    }
    int k = 0;
    for(int i = 0; i < sysCount; i++)
        p[k++] = systemQ[i];
    for(int i = 0; i < userCount; i++)
        p[k++] = userQ[i];
    float totalTAT = 0, totalWT = 0;
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].type,
            p[i].ct, p[i].tat, p[i].wt);

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }
    printf("\nAverage Turnaround Time = %.2f", totalTAT / n);
    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("\nGantt Chart:\n");
    printf(" ");
    for(int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n|");
    for(int i = 0; i < n; i++) {
        printf("  P%d   |", p[i].pid);
    }
    printf("\n ");
    for(int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("\n");
    printf("%d", p[0].start);
    for(int i = 0; i < n; i++) {
        printf("      %d", p[i].ct);
    }
    printf("\n");
    return 0;
}
