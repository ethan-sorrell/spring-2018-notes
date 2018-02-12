/*
  Ethan Sorrell
  Chapter 3 Project 1
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define MAX_LINE 80 /* the maximum length command */

int main(void)
{
    int i;
    pid_t pid;
    char *args[MAX_LINE/2 + 1]; /* command line arguments */ 
    int should_run = 1; /* flag to determine when to exit program */
    int amp_flag = 0;
    char *command;
    char *history[MAX_LINE];
    int history_tail = 0;
    int history_command = 0;

    command = malloc(MAX_LINE);
    for(i=0;i<=10;i++)
        history[i] = malloc(MAX_LINE);

    while(should_run)
    {
        history_command = 0;
        printf("osh>");
        fflush(stdout);

        /*** read user input ***/
        if(!fgets(command, MAX_LINE, stdin)) // read input and check for failure
        {
            // FIXME
            return 0;
        }

        /*** remove trailing newline ***/
        if(command[strlen(command)-1] == '\n')
            command[strlen(command)-1] = '\0';

        /*** check for exit command ***/
        if(strcmp(command, "exit")==0)
        {
            should_run = 0;
            continue;
        }
        /*** check for ! commands ***/
        int num;
        if(command[0] == '!')
        {
            if(command[1] == '!')
            {
                if(history_tail == 0)
                {
                    fprintf(stderr, "No commands in history.\n");
                    continue;
                }
                // exec last command
                strcpy(command, history[(history_tail-1)%10]);
            }
            else if(sscanf(command+1, "%d", &num) != EOF) // reads num
            {
                if(history_tail >= num && history_tail - 10 < num)
                {
                // exec num command
                strcpy(command, history[(num-1)%10]);
                }
                else
                {
                    // error
                    fprintf(stderr, "No such command in history.\n");
                    continue;
                }
            }
            else
            {
                // error
                fprintf(stderr, "No such command in history.\n");
                continue;
            }
            printf("%s\n", command);
        }
        /*** check for history commands ***/
        if(strcmp(command, "history") == 0)
        {
            history_command = 1;
            if(history_tail > 10)
            {
                for(i=history_tail-1; i>=history_tail-10; i--)
                {
                    printf("%d %s\n", i+1, history[i%10]);
                }
            }
            else
            {
                for(i=history_tail-1; i>=0; i--)
                    printf("%d %s\n", i+1, history[i]);
            }
        }

        /*** place command in history ***/
        strcpy(history[history_tail++%10], command);

        /*** check if history command ***/
        if(history_command)
            continue;
        /*** separate command into args ***/
        char *token = strtok(command, " "); 
        int num_args = 0;
        while(token != NULL)
        {
            args[num_args++] = token;
            token = strtok(NULL, " "); 
        }

        /*** check for ampersand ***/
        if(strcmp(args[num_args-1], "&") == 0)
        {
            amp_flag = 1;
            num_args--;
        }

        args[num_args++] = NULL; // add NULL arg

        /*** create child process ***/
        pid = fork();
        if(pid < 0) // error occurred
        {
            fprintf(stderr, "Fork failed\n");
            return 1;
        }

        /*** child process running ***/
        else if(pid == 0)
        {
            execvp(args[0], args);
            should_run = 0;
        }

        /*** parent process running ***/
        else if(pid > 0)
        {
            if(!amp_flag)
                wait(NULL);
        }
    }
    return 0;
}
