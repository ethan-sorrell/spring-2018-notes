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


void addNode(node** head, node* newNext, char* newWord)
{
    node* walk;
    node* new = malloc(sizeof(node));
    new->word = malloc(sizeof(char) * strlen(newWord));
    strcpy(new->word, newWord);
    new->next = newNext;
    if(*head == NULL)
        *head = new;
    else
    {
        walk = *head;
        while(walk->next != NULL)
            walk = walk->next;
        walk->next = new;
    }
}

void push(node** head, char* value)
{
    node* new = malloc(sizeof(node));
    new->word = value;
    new->next = *head;
    *head = new;
}

typedef struct{
    char* top;
    node* list;
}stack;

/*
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
*/

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
        return addNode(&where, NULL, token);

    switch(token[0])
    {
    case ';':
        return;
    case '(':
        addNode(&where, NULL, "(");
        return whereQuery(where, token+1);
    case ')':
        addNode(&where, NULL, ")");
        return whereQuery(where, token+1);
    case '>':
        if(token[1] == '=')
        {
            addNode(&where, NULL, ">=");
            return whereQuery(where, token+2);
        }
        else
        {
            addNode(&where, NULL, ">");
            return whereQuery(where, token+1);
        }
    case '<':
        if(token[1] == '=')
        {
            addNode(&where, NULL, "<=");
            return whereQuery(where, token+2);
        }
        else if(token[1] == '>')
        {
            addNode(&where, NULL, "<>");
            return whereQuery(where, token+2);
        }
        else
        {
            addNode(&where, NULL, "<");
            return whereQuery(where, token+1);
        }
    case '=':
        addNode(&where, NULL, "=");
        return whereQuery(where, token+1);
    }
    uint i;
    for(i=0; i<strlen(token); i++)
    {
        if(!isalnum(token[i]))
        {
            char new[20];
            strncpy(new, token, i);
            addNode(&where, NULL, new);
            return whereQuery(where, token+i);
        }
    }
}
int precedence(char* token)
{
    switch(token[0])
    {
    case '<':
    case '>':
    case '=':
        return 2;
    case 'A':
        return 1;
    case 'O':
        return 0;
    }
    // TODO remove
    return -1;
}

int isOperator(char* token)
{
    if(strcmp(token, ">=") == 0)
        return 1;
    if(strcmp(token, "<=") == 0)
        return 1;
    if(strcmp(token, "<") == 0)
        return 1;
    if(strcmp(token, ">") == 0)
        return 1;
    if(strcmp(token, "<>") == 0)
        return 1;
    if(strcmp(token, "=") == 0)
        return 1;
    if(strcmp(token, "AND") == 0)
        return 1;
    if(strcmp(token, "OR") == 0)
        return 1;
    return 0;
}

int convertWhere(node* where, char** exp)
{
    int i;
    node* walk = where;
    node* s = NULL;
    int j = 0;
    while(walk != NULL)
    {
        // printf("%s\n", walk->word);
        if(strcmp(walk->word, "(") == 0)
            push(&s, walk->word);
        else if(strcmp(walk->word, ")") == 0)
        {
            while(s != NULL && strcmp(s->word, "(") != 0)
            {
                //printf("%s\n", s->word);
                strcpy(exp[j++], s->word);
                s = s->next;
            }
            s = s->next;
        }
        else if(isOperator(walk->word))
        {
            while(s != NULL && precedence(walk->word) <= precedence(s->word))
            {
                strcpy(exp[j++], s->word);
                s = s->next;
            }
            push(&s, walk->word);
        }
        else
        {
            // is operand
            exp[j++] = walk->word;
        }
        walk = walk->next;
    }
    while(s != NULL)
    {
        strcpy(exp[j++], s->word);
        s = s->next;
    }
    for(i = 0; i < j; i++)
        printf("%s", exp[i]);
    printf("\n");
    return j;
}

void fix(query* q)
{
    q->from = q->from->next;
    q->get = q->get->next;
    q->where = q->where->next;
    q->on = q->on->next;
    q->groupby = q->groupby->next;
}

query* parse(FILE* queries)
{
    char token[20];
    query* n = malloc(sizeof(query));
    n->get = NULL;
    n->from = NULL;
    n->where = NULL;
    n->on = NULL;
    n->groupby = NULL;

    fscanf(queries, "%s", token);
    if(strcmp(token, "GET") == 0)
    {
        // read GET
        fscanf(queries, "%s", token);
        while(strcmp(token, "FROM") != 0)
        {
            if(token[strlen(token)-1] == ',')
                token[strlen(token)-1] = '\0';
            addNode(&n->get, NULL, token);
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
        addNode(&n->from, NULL, token);
        return n;
    }
    addNode(&n->from, NULL, token);
    fscanf(queries, "%s", token);
    if(strcmp(token, "COMBINE") == 0)
    {
        fscanf(queries, "%s", token);
        addNode(&n->from, NULL, token);
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

void filter(FILE* temp, char** exp, FILE* filtered, node* table)
{
    char* row;
    char format[100];
    int flag = 1;
    node* walk = table;
    while(walk != NULL)
    {
        if(strlen(format) != 0)
            strcat(format, ",");
        if(strcmp(walk->word, "T1A") == 0)
            strcat(format, "%d,%d,%d,%d");
        if(strcmp(walk->word, "T1B") == 0)
            strcat(format, "%d,%d,%d,%d,%d");
        if(strcmp(walk->word, "T2") == 0)
            strcat(format, "%d,%d,%d,%d,%d");
        walk = walk->next;
    }
    printf("%s\n", format);
}

void retrieve(query* q)
{
    FILE* temp;
    FILE* filtered = fopen("filtered.txt", "w");
    node* table = NULL;
    // fix(q);

    // first open file in FROM
    if(q->from->next != NULL)
    {
        // must perform combine
    }
    if(strcmp(q->from->word, "T1A") == 0)
    {
        temp = fopen("T1A.txt", "r");
        addNode(&table, NULL, "T1A");
    }
    if(strcmp(q->from->word, "T1B") == 0)
    {
        temp = fopen("T1B.txt", "r");
        addNode(&table, NULL, "T1B");
    }
    if(strcmp(q->from->word, "T2") == 0)
    {
        temp = fopen("T2.txt", "r");
        addNode(&table, NULL, "T2");
    }
    table = table->next;
    // then find rows that satisfy WHERE
    char** exp = malloc(sizeof(char*) * 40);
    int i;
    for(i = 0; i < 40; i++)
        exp[i] = malloc(sizeof(char) * 20);
    int len = convertWhere(q->where, exp);
    filter(temp, exp, filtered, table);
    // printf("%d\n",len);


    //fclose(temp);
}

int main()
{
    // t1a = fopen("T1A.txt", "r");
    // t1b = fopen("T1B.txt", "r");
    // t2  = fopen("T2.txt", "r");
    FILE* queries = fopen("queries.txt", "r");

    query* thisQuery = parse(queries);
    /*
    node* walk = thisQuery->where;
    while(walk!=NULL)
    {
        printf("%s\n",walk->word);
        walk = walk->next;
    }
    */
    retrieve(thisQuery);


    // fclose(t1a); fclose(t1b);
    // fclose(t2);  fclose(queries);
    return 0;
}
