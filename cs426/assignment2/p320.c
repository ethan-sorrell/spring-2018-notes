/*
  Created by Ethan Sorrell
*/
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000

int *pid_bitmap;

int allocate_map(void)
{
    pid_bitmap = malloc(sizeof(int) * 5001);

    if(pid_bitmap == NULL)
        return -1;

    /* bitmap successfully allocated */
    int i;
    for(i = MIN_PID; i <= MAX_PID; i++)
        pid_bitmap[i] = 0;
    return 1;
}

int allocate_pid(void)
{
    int new_id = -1;
    int i;

    /* loop through bitmap looking for unallocated pid */
    for(i = MIN_PID; i <= MAX_PID; i++)
    {
        if(pid_bitmap[i] == 0)
        {
            pid_bitmap[i] = 1;
            new_id = i;
            break;
        }
    }
    return new_id;
}

void release_pid(int pid)
{
    if(pid > MAX_PID || pid < MIN_PID)
        return;

    /* a valid pid was passed */
    pid_bitmap[pid] = 0;
}
