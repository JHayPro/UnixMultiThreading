#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define VALUES_SIZE 7
int values[VALUES_SIZE] = {90, 81, 78, 95, 79, 72, 85};

int min, max;
double ave;

void *average(void *arg)
{
    for (int i = 0; i < VALUES_SIZE; i++)
        ave += values[i];

    ave /= VALUES_SIZE;

    return NULL;
}
void *minimum(void *arg)
{
    min = values[0];
    for (int i = 0; i < VALUES_SIZE; i++)
        if (min > values[i])
            min = values[i];
    return NULL;
}
void *maximum(void *arg)
{
    max = values[0];
    for (int i = 0; i < VALUES_SIZE; i++)
        if (max < values[i])
            max = values[i];
}

int main()
{
    pthread_t aveThread, miniThread, maxThread;

    pthread_create(&aveThread, NULL, average, NULL);
    pthread_create(&miniThread, NULL, minimum, NULL);
    pthread_create(&maxThread, NULL, maximum, NULL);
    pthread_join(aveThread, NULL); 
    pthread_join(miniThread, NULL);
    pthread_join(maxThread, NULL);

    printf("The Average Value Is %lf",ave);
    printf("\nThe Minimum Value Is %d",min);
    printf("\nThe Maximum Value Is %d",max);
    printf("\n");
}