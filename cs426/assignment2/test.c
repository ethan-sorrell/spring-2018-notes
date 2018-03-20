#include "p320.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    allocate_map();
    int i = allocate_pid();
    printf("%d\n", i);
    return 0;
}
