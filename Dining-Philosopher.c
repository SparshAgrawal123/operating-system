#include <stdio.h>
#include <stdlib.h>

int n, h;
int pos[10];   // positions of hungry philosophers

// check if philosopher can eat
int canEat(int p, int eating[], int size) {
    for (int i = 0; i < size; i++) {
        // adjacent philosophers (circular table)
        if (abs(p - eating[i]) == 1 || abs(p - eating[i]) == n - 1)
            return 0;
    }
    return 1;
}

void oneEat() {
    int eating[10], count = 0;

    printf("Allow one philosopher to eat at any time\n");

    for (int i = 0; i < h; i++) {
        printf("P %d is waiting\n", pos[i]);
    }

    for (int i = 0; i < h; i++) {
        if (canEat(pos[i], eating, count)) {
            eating[count++] = pos[i];
            printf("P %d is granted to eat\n", pos[i]);
            printf("P %d has finished eating\n", pos[i]);
        }
    }
}

void twoEat() {
    int eating[10], count = 0;

    printf("Allow two philosophers to eat at a time\n");

    for (int i = 0; i < h; i++) {
        printf("P %d is waiting\n", pos[i]);
    }

    for (int i = 0; i < h; i++) {
        if (count < 2 && canEat(pos[i], eating, count)) {
            eating[count++] = pos[i];
            printf("P %d is granted to eat\n", pos[i]);
        }
    }

    for (int i = 0; i < count; i++) {
        printf("P %d has finished eating\n", eating[i]);
    }
}

int main() {
    int choice;

    printf("Enter the total number of philosophers: ");
    scanf("%d", &n);

    printf("How many are hungry: ");
    scanf("%d", &h);

    for (int i = 0; i < h; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, n);
        scanf("%d", &pos[i]);
    }

    while (1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: oneEat(); break;
            case 2: twoEat(); break;
            case 3: exit(0);
            default: printf("Invalid choice\n");
        }
    }

    return 0;
}
