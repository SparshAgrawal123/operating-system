#include <stdio.h>
#include <math.h>
#define MAX 10
typedef struct {
    int id;
    int C; // Execution time
    int T; // Period
    int remaining_time;
} Task;

// Function to find GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Sort tasks by period (ascending)
void sortByPeriod(Task tasks[], int n) {
    Task temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tasks[i].T > tasks[j].T) {
                temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Task tasks[MAX];
    float U = 0, bound;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d:\n", i + 1);

        printf("Execution Time (C): ");
        scanf("%d", &tasks[i].C);

        printf("Period (T): ");
        scanf("%d", &tasks[i].T);

        tasks[i].remaining_time = 0;
    }

    // Step 1: CPU Utilization
    for (int i = 0; i < n; i++) {
        U += (float)tasks[i].C / tasks[i].T;
    }

    // Step 2: RMS Bound
    bound = n * (pow(2, 1.0 / n) - 1);

    printf("\nCPU Utilization (U) = %.4f\n", U);
    printf("RMS Bound = %.4f\n", bound);

    // Step 3: Schedulability
    if (U <= bound)
        printf("Schedulable using RMS\n");
    else
        printf("Not guaranteed schedulable\n");

    // Step 4: Priority assignment
    sortByPeriod(tasks, n);

    printf("\nPriority Order (Shortest Period = Highest Priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d (T=%d)\n", tasks[i].id, tasks[i].T);
    }

    // Step 5: Calculate Hyperperiod using LCM
    int hyperperiod = tasks[0].T;
    for (int i = 1; i < n; i++) {
        hyperperiod = lcm(hyperperiod, tasks[i].T);
    }

    printf("\nHyperperiod = %d\n", hyperperiod);

    // Scheduling
    printf("\nScheduling Timeline:\n");

    for (int time = 0; time < hyperperiod; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].T == 0) {
                tasks[i].remaining_time = tasks[i].C;
            }
        }

        // Select highest priority ready task
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                selected = i;
                break;
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d running\n", time, tasks[selected].id);
            tasks[selected].remaining_time--;
        } else {
            printf("Time %d: Idle\n", time);
        }
    }

    return 0;
}
