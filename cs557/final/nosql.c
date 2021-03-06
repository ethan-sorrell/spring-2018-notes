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

node* newNode()
{
    node* new = malloc(sizeof(node));
    new->word = malloc(sizeof(char) * 50);
    return new;
}

void addNode(node* list, node* newNext, char* newWord)
{
    node* walk;
    /*
    node* new = newNode();
    char* aword = malloc(sizeof(char) * strlen(newWord));
    */
    node* new = malloc(sizeof(node));
    new->word = malloc(sizeof(char) * strlen(newWord));
    // strcpy(aword, newWord);
    // new->word = aword;
    strcpy(new->word, newWord);
    new->next = newNext;
    if(list == NULL)
        *list = *new;
    else
    {
        walk = list;
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
    n->get = newNode();
    n->from = newNode();
    n->where = newNode();
    n->on = newNode();
    n->groupby = newNode();

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

char* eval(char* op1, char* op, char* op2)
{
    char *result = malloc(sizeof(char) * 4);
    int opA = strtol(op2, NULL, 10);
    int opB = strtol(op1, NULL, 10);
    if(strcmp(op, "=") == 0)
        sprintf(result, "%d", opA==opB);
    else if(strcmp(op, ">") == 0)
        sprintf(result, "%d", opA>opB);
    else if(strcmp(op, "<") == 0)
        sprintf(result, "%d", opA<opB);
    else if(strcmp(op, ">=") == 0)
        sprintf(result, "%d", opA>=opB);
    else if(strcmp(op, "<=") == 0)
        sprintf(result, "%d", opA<=opB);
    else if(strcmp(op, "<>") == 0)
        sprintf(result, "%d", opA!=opB);
    return result;
}

void translate(char* token,char* columnNames,char* row, char* r)
{
    char cnames[100];
    char ro[100];
    strcpy(cnames, columnNames);
    strcpy(ro, row);
    char* search = strtok(cnames, ",");
    int i=1;
    while(strcmp(search, token) != 0)
    {
        search = strtok(NULL, ",");
        i++;
    }
    int j=1;
    char* result = strtok(ro, ",");
    for(j=1; j<i; j++)
        result = strtok(NULL, ",");
    strncpy(r, result, strlen(result));
}

void filter(FILE* temp, char** exp, int len, FILE* filtered, node* table)
{
    char row[100];
    char format[100];
    char columnNames[100];
    int flag = 0;
    node* walk = table;
    int numCols = 0;
    char t[20];
    while(walk != NULL)
    {
        if(strlen(format) != 0)
        {
            strcat(format, ",");
            strcat(columnNames, ",");
        }
        if(strcmp(walk->word, "T1A") == 0)
        {
            strcat(format, "%d,%d,%d,%d");
            strcat(columnNames, "K1,TS,C1,C2");
            numCols += 4;
        }
        if(strcmp(walk->word, "T1B") == 0)
        {
            strcat(format, "%d,%d,%d,%d,%d");
            strcat(columnNames, "K1,TS,C3,C4,C5");
            numCols += 5;
        }
        if(strcmp(walk->word, "T2") == 0)
        {
            strcat(format, "%d,%d,%d,%d,%d");
            strcat(columnNames, "K2,TS2,A1,A2,A3");
            numCols += 5;
        }
        walk = walk->next;
    }
    int i = 0;
    while(fgets(row, 100, temp))
    {
        node* s = NULL;
        char* op1, *op2;
        char tOp1[10], tOp2[10];
        for(i=0; i<len; i++)
        {
            if(isOperator(exp[i]))
            {
                op1 = s->word;
                s = s->next;
                op2 = s->word;
                s = s->next;
                if(!isalpha(exp[i][0]))
                {
                    if(isalpha(op1[0]))
                        translate(op1, columnNames, row, tOp1);
                    else
                        strcpy(tOp1, op1);
                    if(isalpha(op2[0]))
                        translate(op2, columnNames, row, tOp2);
                    else
                        strcpy(tOp2, op2);
                }
                push(&s, eval(tOp1, exp[i], tOp2));
            }
            else //is operand
                push(&s, exp[i]);
        }
        if(strcmp(s->word, "1") == 0)
            printf("%s\n",row);
        s = s->next;
    }
}

void retrieve(query* q)
{
    FILE* temp;
    FILE* filtered = fopen("filtered.txt", "w");
    node* table = newNode();
    fix(q);

    // first open file in FROM
    if(q->from->next != NULL)
    {
        // must perform combine
    }
    if(strcmp(q->from->word, "T1A") == 0)
    {
        temp = fopen("T1A.txt", "r");
        addNode(table, NULL, "T1A");
    }
    if(strcmp(q->from->word, "T1B") == 0)
    {
        temp = fopen("T1B.txt", "r");
        addNode(table, NULL, "T1B");
    }
    if(strcmp(q->from->word, "T2") == 0)
    {
        temp = fopen("T2.txt", "r");
        addNode(table, NULL, "T2");
    }
    table = table->next;
    // then find rows that satisfy WHERE
    char** exp = malloc(sizeof(char*) * 40);
    int i;
    for(i = 0; i < 40; i++)
        exp[i] = malloc(sizeof(char) * 20);
    int len = convertWhere(q->where, exp);
    filter(temp, exp, len, filtered, table);
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
