#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* t1a;
FILE* t1b;
FILE* t2;

typedef struct Node{
    struct Node* next;
    char* word;
}node;

void addNode(node* list, node* newNext, char* newWord)
{
    node* walk;
    node* new = malloc(sizeof(node));
    char* aword = malloc(sizeof(char) * strlen(newWord));
    strcpy(aword, newWord);
    new->word = aword;
    new->next = newNext;
    if(list == NULL)
        list = new;
    else
    {
        walk = list;
        while(walk->next != NULL)
            walk = walk->next;
        walk->next = new;
    }
}

typedef struct{
    char* top;
    node* list;
}stack;

void push(stack* s, char* value)
{
    addNode(s->list, NULL, value);
    node* walk = s->list;
    while(walk->next != NULL)
    {
        walk = walk->next;
    }
    s->top = walk->word;
}
char* pop(stack* s)
{
    node* walk = s->list;
    if(walk->next == NULL)
    {
        s->list = NULL;
        s->top = NULL;
        return walk->word;
    }
    while(walk->next->next != NULL)
        walk = walk->next;
    char* word = walk->next->word;
    walk->next = NULL;
    s->top = walk->word;
    return word;
}

typedef struct{
    node* get;
    node* from; //NOTE: more than one word in list means combine
    node* on;
    node* where;
    node* groupby;
}query;

void whereQuery(node* where, char* token)
{
    if(strlen(token) == 0)
        return;
    if(strcmp(token, "AND") == 0 || strcmp(token, "OR") == 0)
        return addNode(where, NULL, token);

    switch(token[0])
    {
    case ';':
        return;
    case '(':
        addNode(where, NULL, "(");
        return whereQuery(where, token+1);
    case ')':
        addNode(where, NULL, ")");
        return whereQuery(where, token+1);
    case '>':
        if(token[1] == '=')
        {
            addNode(where, NULL, ">=");
            return whereQuery(where, token+2);
        }
        else
        {
            addNode(where, NULL, ">");
            return whereQuery(where, token+1);
        }
    case '<':
        if(token[1] == '=')
        {
            addNode(where, NULL, "<=");
            return whereQuery(where, token+2);
        }
        else if(token[1] == '>')
        {
            addNode(where, NULL, "<>");
            return whereQuery(where, token+2);
        }
        else
        {
            addNode(where, NULL, "<");
            return whereQuery(where, token+1);
        }
    case '=':
        addNode(where, NULL, "=");
        return whereQuery(where, token+1);
    }
    uint i;
    for(i=0; i<strlen(token); i++)
    {
        if(!isalnum(token[i]))
        {
            char new[20];
            strncpy(new, token, i);
            addNode(where, NULL, new);
            return whereQuery(where, token+i);
        }
    }
}


query* parse(FILE* queries)
{
    char token[20];
    query* n = malloc(sizeof(query));
    fscanf(queries, "%s", token);
    if(strcmp(token, "GET") == 0)
    {
        // read GET
        fscanf(queries, "%s", token);
        while(strcmp(token, "FROM") != 0)
        {
            if(token[strlen(token)-1] == ',')
                token[strlen(token)-1] = '\0';
            addNode(n->get, NULL, token);
            fscanf(queries, "%s", token);
        }
    }
    else
    {
        // ?
    }
    if(strcmp(token, "FROM") != 0)
    {
        // ?
    }
    // read FROM
    fscanf(queries, "%s", token);
    if(token[strlen(token)-1] == ';')
    {
        token[strlen(token)-1] = '\0';
        addNode(n->from, NULL, token);
        return n;
    }

    addNode(n->from, NULL, token);
    fscanf(queries, "%s", token);
    if(strcmp(token, "COMBINE") == 0)
    {
        fscanf(queries, "%s", token);
        addNode(n->from, NULL, token);
        // TODO add "on" condition
    }
    if(strcmp(token, "WHERE") != 0)
    {
        // ?
    }
    while(fscanf(queries, "%s", token) == 1)
    {
        if(strcmp(token, "GROUP") == 0)
        {
        }
        whereQuery(n->where, token);
        if(token[strlen(token)-1] == ';')
            return n;
    }
    return n;
}

void retrieve(query* q)
{
    if(q->from->next != NULL)
    {
        // must perform combine
    }
    if()
}

int main()
{
    t1a = fopen("T1A.txt", "r");
    t1b = fopen("T1B.txt", "r");
    t2  = fopen("T2.txt", "r");
    FILE* queries = fopen("queries.txt", "r");

    query* thisQuery = parse(queries);
    retrieve(thisQuery);


    fclose(t1a); fclose(t1b);
    fclose(t2);  fclose(queries);
    return 0;
}
