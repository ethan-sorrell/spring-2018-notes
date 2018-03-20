/*
  Ethan Sorrell
  Problem 3.21
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

/*** helper function ***/
void collatz(int n)
{
    if(n == 1)
    {
        printf("%d\n", n);
        return;
    }
    printf("%d,",n);

    if(n%2 == 0) // n is even
        collatz(n/2);
    else // n is odd
        collatz(3*n+1);
}

/*** main function ***/
int main(int argc, char** argv)
{
    pid_t pid;

    if(argc < 2)
    {
        fprintf(stderr, "program requires a positive integer as an argument\n");
        return 1;
    }

    int n = atoi(argv[1]); // parse arg

    if(n <= 0)
    {
        fprintf(stderr, "argument must be a positive integer\n");
        return 1;
    }

    /*** fork program ***/
    pid = fork();
    if(pid < 0) // fork failed
    {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if(pid == 0) // child process
        collatz(n);
    else // parent process
        wait(NULL);

    return 0;
}
