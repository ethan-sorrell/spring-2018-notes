/*
 * Usage: accuse
 * (reads one line from standard input)
 *
 * To compile:
 * cc accuse.c - o accuse
 *
 * Install under inetd as follows:
 *  accuse stream tcp nowait root /path/to/ acc use accuse *
 * Copyright 2003 by Bob T . Coder, PhD.
 */
#include <stdio.h>
#include <string.h>
#define INPUT_BUFFER 256  /* maximum name size */
/*
 * read input, copy into s 
 */
void get_line(char *s)
{
    int c;
    while ((c=getchar()) != EOF)
        *s++ = c;
    *s = '\0';
}
/*
 * convert newlines to nulls in place
 */
void removenewlines(char *s)
{
    int l;
    l = strlen(s);
    while (l--)
        if (s[l] == '\n')
            s[l] = '\0';
}
int main()
{
    char victim[INPUT_BUFFER];
    get_line(victim);
    /* this check ensures there's no buffer overflow */
    if (strlen(victim) < INPUT_BUFFER) {
        removenewlines(victim);
        printf("It's all %s's fault.\n", victim);
    }
    return 0;
}
