#include <stdio.h>

int mutex = 1;
int full = 0;
int empty = 3;   // buffer size
int x = 0;       // item count

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    if (mutex == 1 && empty != 0) {
        wait(&mutex);
        wait(&empty);
        wait(&full);

        x++;
        printf("Producer produces item %d\n", x);

        signal(&mutex);
    } else {
        printf("Buffer is full!\n");
    }
}

void consumer() {
    if (mutex == 1 && full != 0) {
        wait(&mutex);
        wait(&full);
        wait(&empty);

        printf("Consumer consumes item %d\n", x);
        x--;

        signal(&mutex);
    } else {
        printf("Buffer is empty!\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Produce  2. Consume  3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: producer(); break;
            case 2: consumer(); break;
            case 3: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
