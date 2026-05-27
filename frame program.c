#include <stdio.h>
int frames[10], pages[50], n, f;
int search(int key)
{
    for(int i = 0; i < f; i++)
        if(frames[i] == key)
            return 1;
    return 0;
}
void display()
{
    for(int i = 0; i < f; i++)
        (frames[i] != -1) ? printf("%d ", frames[i]) : printf("- ");
    printf("\n");
}
void FIFO()
{
    int faults = 0, index = 0;
    for(int i = 0; i < f; i++) frames[i] = -1;
    printf("\nFIFO Page Replacement:\n");
    for(int i = 0; i < n; i++)
    {
        if(!search(pages[i]))
        {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
            printf("PF No. %d: ", faults);
            display();
        }
    }
    printf("FIFO Page Faults: %d\n", faults);
}
void LRU()
{
    int time[10] = {0}, faults = 0, count = 0;
    for(int i = 0; i < f; i++) frames[i] = -1;
    printf("\nLRU Page Replacement:\n");
    for(int i = 0; i < n; i++)
    {
        int found = 0;
        for(int j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                time[j] = ++count;
                found = 1;
            }
        }
        if(!found)
        {
            int pos = 0;
            for(int j = 1; j < f; j++)
                if(time[j] < time[pos])
                    pos = j;
            frames[pos] = pages[i];
            time[pos] = ++count;
            faults++;
            printf("PF No. %d: ", faults);
            display();
        }
    }
    printf("LRU Page Faults: %d\n", faults);
}
void Optimal()
{
    int faults = 0;
    for(int i = 0; i < f; i++) frames[i] = -1;
    printf("\nOptimal Page Replacement:\n");
    for(int i = 0; i < n; i++)
    {
        if(!search(pages[i]))
        {
            int pos = -1, farthest = i;
            for(int j = 0; j < f; j++)
            {
                int k;
                for(k = i + 1; k < n; k++)
                    if(frames[j] == pages[k]) break;
                if(k > farthest)
                {
                    farthest = k;
                    pos = j;
                }
                if(frames[j] == -1)
                {
                    pos = j;
                    break;
                }
            }
            frames[pos] = pages[i];
            faults++;
            printf("PF No. %d: ", faults);
            display();
        }
    }
    printf("Optimal Page Faults: %d\n", faults);
}
int main()
{
    printf("Enter the number of Frames: ");
    scanf("%d", &f);
    printf("Enter the length of reference string: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    FIFO();
    LRU();
    Optimal();
    return 0;
}
