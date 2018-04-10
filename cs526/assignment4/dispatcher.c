#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct
{
    int arrival;
    int priority;
    int total_tick;
    int elapsed_tick;

    int started;
    pid_t pid;

}proc;

typedef struct
{
    proc* sys_queue[1000];
    int sys_enter;
    int sys_current;

    proc* p1_queue[1000];
    int p1_enter;
    int p1_current;

    proc* p2_queue[1000];
    int p2_enter;
    int p2_current;

    proc* p3_queue[1000];
    int p3_enter;
    int p3_current;
}queues;

int partition (proc** list, int lo, int hi)
{
    // standard qsort partition algorithm
    // adapted to sort by proc arrival time
    int pivot = list[hi]->arrival;
    int i = (lo - 1);
    proc* temp;

    for (int j = lo; j <= hi - 1; j++)
    {
        if (list[j]->arrival <= pivot)
        {
            i++;
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    temp = list[i+1];
    list[i+1] = list[hi];
    list[hi] = temp;

    return (i + 1);
}

void quickSort(proc** list, int lo, int hi)
{
    // standard qsort
    if (lo < hi)
    {
        int pi = partition(list, lo, hi);

        quickSort(list, lo    , pi - 1);
        quickSort(list, pi + 1, hi);
    }
}

pid_t startProcess()
{
    char *arg[2] = {"./process", NULL};
    pid_t pid = fork();
    if(pid < 0) // error occurred
    {
        fprintf(stderr, "Fork failed\n");
        return -1;
    }

    /*** child process running ***/
    else if(pid == 0)
    {
        execvp(arg[0], arg);
        fprintf(stderr, "Passed execvp\n");
    }
    return pid;
}

void suspendProcess(pid_t pid)
{
    kill(pid, SIGTSTP);
    waitpid(pid, NULL, WUNTRACED);
}

void terminateProcess(pid_t pid)
{
    kill(pid, SIGINT);
    waitpid(pid, NULL, WUNTRACED);
}

void restartProcess(pid_t pid)
{
    kill(pid, SIGCONT);
}

int main(int argc, char **argv)
{
    // init dispatcher
    int current_tick = 0;
    queues* m = malloc(sizeof(queues));
    m->sys_enter = 0; m->p1_enter = 0;
    m-> p2_enter = 0; m->p3_enter = 0;

    m->sys_current = 0; m->p1_current = 0;
    m-> p2_current = 0; m->p3_current = 0;

    // open process list
    if(argc != 2)
    {
        printf("Requires 1 command line arguments: dispatchlist\n");
    }
    FILE* dispatch_list = fopen(argv[1], "r");

    // parse process list
    int num1, num2, num3;
    while(fscanf(dispatch_list, "%d, %d, %d", &num1, &num2, &num3) > 0)
    {
        proc* new_proc = malloc(sizeof(proc));
        new_proc->arrival = num1;
        new_proc->priority = num2;
        new_proc->total_tick = num3;
        new_proc->started = 0;

        switch(new_proc->priority)
        {
        case 0:
            m->sys_queue[m->sys_enter++] = new_proc;
            break;
        case 1:
            m->p1_queue[m->p1_enter++] = new_proc;
            break;
        case 2:
            m->p2_queue[m->p2_enter++] = new_proc;
            break;
        case 3:
            m->p3_queue[m->p3_enter++] = new_proc;
            break;
        }
    }

    // sort queues based on arrival time
    quickSort(m->sys_queue, 0, m->sys_enter-1);
    quickSort(m->p1_queue,  0, m->p1_enter-1);
    quickSort(m->p2_queue,  0, m->p2_enter-1);
    quickSort(m->p3_queue,  0, m->p3_enter-1);

    // run dispatching loop
    while(1)
    {
        if( m->sys_current < m->sys_enter &&
            m->sys_queue[m->sys_current]->arrival <= current_tick)
        {
            m->sys_queue[m->sys_current]->started = 1;
            m->sys_queue[m->sys_current]->pid = startProcess();

            // sleep for process duration then kill process
            sleep(m->sys_queue[m->sys_current]->total_tick);
            terminateProcess(m->sys_queue[m->sys_current]->pid);

            current_tick += m->sys_queue[m->sys_current]->total_tick;
            m->sys_current++;
        }
        else if(m->p1_current < m->p1_enter &&
                m->p1_queue[m->p1_current]->arrival <= current_tick)
        { // check priority 1 queue
            { // process must be started
                m->p1_queue[m->p1_current]->started = 1;
                m->p1_queue[m->p1_current]->pid = startProcess();

                // sleep for 1 tick then pause or kill process
                sleep(1);
                if(m->p1_queue[m->p1_current]->total_tick <= ++m->p1_queue[m->p1_current]->elapsed_tick)
                { // process finished
                    terminateProcess(m->p1_queue[m->p1_current]->pid);
                    m->p1_current++;
                }
                else
                {
                    suspendProcess(m->p1_queue[m->p1_current]->pid);
                    // move to lower priority queue
                    m->p2_queue[m->p2_enter++] = m->p1_queue[m->p1_current++];
                }
                current_tick += 1;
            }
        }
        else if(m->p2_current < m->p2_enter &&
                m->p2_queue[m->p2_current]->arrival <= current_tick)
        { // check priority 2 queue
            if(m->p2_queue[m->p2_current]->started)
            { //process must be resumed
                restartProcess(m->p2_queue[m->p2_current]->pid);
            }
            else
            { // process must be started
                m->p2_queue[m->p2_current]->started = 1;
                m->p2_queue[m->p2_current]->pid = startProcess();
            }

            // sleep for tick then pause or kill process
            sleep(1);
            if(m->p2_queue[m->p2_current]->total_tick <= ++m->p2_queue[m->p2_current]->elapsed_tick)
            { // process finished
                terminateProcess(m->p2_queue[m->p2_current]->pid);
                m->p2_current++;
            }
            else
            { // process not yet finished
                suspendProcess(m->p2_queue[m->p2_current]->pid);
                // move to lower priority queue
                m->p3_queue[m->p3_enter++] = m->p2_queue[m->p2_current++];
            }

            current_tick += 1;
        }
        else if(m->p3_current < m->p3_enter &&
                m->p3_queue[m->p3_current]->arrival <= current_tick)
        { // check priority 3 queue
            if(m->p3_queue[m->p3_current]->started)
            { //process must be resumed
                restartProcess(m->p3_queue[m->p3_current]->pid);
            }
            else
            { // process must be started
                m->p3_queue[m->p3_current]->started = 1;
                m->p3_queue[m->p3_current]->pid = startProcess();
            }

                // sleep for tick then pause or kill process
                sleep(1);
                if(m->p3_queue[m->p3_current]->total_tick <= ++m->p3_queue[m->p3_current]->elapsed_tick)
                { // process finished
                    terminateProcess(m->p3_queue[m->p3_current]->pid);
                    m->p3_current++;
                }
                else // process not finished
                    suspendProcess(m->p3_queue[m->p3_current]->pid);

                current_tick += 1;
        }
        else if(m->sys_current < m->sys_enter ||
                m->p1_current < m->p1_enter ||
                m->p2_current < m->p2_enter ||
                m->p3_current < m->p3_enter)
        {
            current_tick += 1;
            continue;
        }
        else
            break;
    }

    return 0;
}

