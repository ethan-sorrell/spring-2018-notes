#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char* from;
    char* to;
}FD;

typedef struct{
    char* columns;
    char** candidateKeys;
    int numKeys;
    FD* dependencies;
    int numFDs;
}relation;

int inKey(char* token, relation* thisRelation)
{
    int  j;
    for(j = 0; j < thisRelation->numKeys; j++)
    {
        if(!strcmp(token, thisRelation->candidateKeys[j]))
        {
            return 1;
        }
    }
    return 0;
}

int thirdNF(relation* thisRelation)
{
    int i, j;
    for(i = 0; i < thisRelation->numFDs; i++)
    {
        if(inKey(thisRelation->dependencies[i].from, thisRelation)
           && !inKey(thisRelation->dependencies[i].to, thisRelation))
        {
            for(j = 0; j < thisRelation->numFDs; j++)
            {
                if( !strcmp(thisRelation->dependencies[i].to, thisRelation->dependencies[j].from)
                    && !inKey(thisRelation->dependencies[j].to, thisRelation) )
                    {
                        return 0;
                    }
            }
        }
    }
    return 1;
}

int secondNF(relation* thisRelation)
{
    int i, j;
    for(i = 0; i < thisRelation->numFDs; i++)
    {
        for(j = 0; j < thisRelation->numKeys; j++)
        {
            if(
                strstr(thisRelation->candidateKeys[j], thisRelation->dependencies[i].from) != NULL
               &&
               strcmp(thisRelation->dependencies[i].from, thisRelation->candidateKeys[j]))
            {
                return 0;
            }

        }
    }
    return 1;
}

int main(void)
{
    FILE* fin = fopen("HW7in.txt", "r");
    FILE* fout = fopen("HW7esorrell.txt", "w");
    char str[100];
    char* token;
    fgets(str, 100, fin);
    while(str != NULL)
    {
        relation* newRelation = malloc(sizeof(relation));
        token = strtok(str, " ");
        newRelation->columns = token; // stores columns of relation

        newRelation->numKeys = 0;
        newRelation->candidateKeys = malloc(sizeof(char*) * 20);

        /* stores all candidate keys of relation */
        token = strtok(NULL, " ");
        while(!strchr(token, ';'))
        {
            // printf("token is %s\n", token);
            newRelation->candidateKeys[newRelation->numKeys] = malloc(sizeof(char*) * 20);
            strcpy(newRelation->candidateKeys[newRelation->numKeys++], token);
            token = strtok(NULL, " ");
        }
        *strchr(token, ';') = '\0';
        newRelation->candidateKeys[newRelation->numKeys] = malloc(sizeof(char*) * 20);
        strcpy(newRelation->candidateKeys[newRelation->numKeys++], token);
        // printf("token is %s\n", token);

        /* store all dependencies of relation */
        newRelation->numFDs = 0;
        newRelation->dependencies = malloc(sizeof(FD*) * 100);
        fgets(str, 100, fin);
        while(1)
        {
            if(strchr(str, 'x'))
                break;

            FD* newFD = malloc(sizeof(FD));
            newFD->from = malloc(sizeof(char*) * 10);
            newFD->to = malloc(sizeof(char*) * 10);

            token = strtok(str, ")");
            strcpy(newFD->from, &token[1]);
            // strncpy(newFD->from, &token[1], strlen(token));
            token = strtok(NULL, ")");
            strcpy(newFD->to, &token[1]);
            newRelation->dependencies[newRelation->numFDs++] = *newFD;

            fgets(str, 100, fin);
        }
        /* determine normal form and output */
        if(secondNF(newRelation))
        {
            if(thirdNF(newRelation))
            {
                printf("3NF\n");
                fprintf(fout, "3NF\n");

            }
            else
            {
                
                printf("2NF\n");
                fprintf(fout, "2NF\n");
            }
        }
        else
        {
            printf("1NF\n");
            fprintf(fout, "1NF\n");
        }
        // printf("2nf? %d\n",secondNF(newRelation));
        // printf("3nf? %d\n",thirdNF(newRelation));


        if(fgets(str, 100, fin) == NULL)
            break;
    }
}
