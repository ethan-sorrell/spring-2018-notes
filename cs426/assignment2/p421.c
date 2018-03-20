/*
  Created by Ethan Sorrell
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *min_func(void*);
void *max_func(void*);
void *avg_func(void*);

/* global variables for our child processes to modify/read */
int avg = 0;
int min,max;
int num_args;
int *num;

int main(int argc, char **argv)
{
    /* input checking */
    if(argc < 2)
    {
        fprintf(stderr, "This program requires a list of numbers as arguments\n");
        return -1;
    }
    num_args = argc;
    num = malloc(sizeof(int) * argc);

    /* converting cmdline arg strings into ints */
    int i;
    for(i = 1; i < argc; i++)
        sscanf(argv[i], "%d", &num[i]);

    pthread_t tid[3];
    /* create child processes */
    pthread_create(&tid[0], NULL, avg_func, NULL);
    pthread_create(&tid[1], NULL, min_func, NULL);
    pthread_create(&tid[2], NULL, max_func, NULL);

    /* wait for processes to finish */
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    printf("The average value is %d\nThe minimum value is %d\nThe maximum value is %d\n"
           ,avg, min, max);
    return 0;
}

void *min_func(void *param)
{
    int i;
    min = num[1];
    for(i = 2; i < num_args; i++)
        if(num[i] < min)
            min = num[i];
    pthread_exit(0);
}
void *max_func(void *param)
{
    int i;
    max = num[1];
    for(i = 2; i < num_args; i++)
        if(num[i] > max)
            max = num[i];
    pthread_exit(0);
}
void *avg_func(void *param)
{
    int i;
    for(i = 1; i < num_args; i++)
        avg += num[i];
    avg /= (num_args - 1);
    pthread_exit(0);
}
