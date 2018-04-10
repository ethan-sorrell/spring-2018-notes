#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int front = -1;
int back = -1;

int run = 1;


int insert_item(buffer_item item)
{
    { /* this block should be unnecessary */
        if((front == 0 && back == BUFFER_SIZE-1) || (back == front-1))
            return -1; // queue is full somehow?
    }
    /* fix circular index */
    if(front == -1)
        front = back = 0;
    else if(back == BUFFER_SIZE-1)
        back = 0;
    else
        back++;

    /* insert item into buffer */
    buffer[back] = item;

    return 0;
}

int remove_item(buffer_item *item)
{
    { /* this block should be unnecessary */
        if(front == -1)
            return -1;
    }
    /* place front buffer value in item */
    *item = buffer[front];

    /* fix index */
    if(front == back)
        front = back = -1;
    else if(front == BUFFER_SIZE-1)
        front = 0;
    else
        front++;


    return 0;
}

void *consumer(void *param)
{
    buffer_item item;
    pthread_t tid = pthread_self();
    int sleep_dur;
    int size;

    while(run)
    {
        /* sleep for random duration */
        sleep_dur = rand() % 5;
        printf("%lu (consumer) sleeping for %ds\n", tid, sleep_dur);
        sleep(sleep_dur);

        /* acquire semaphores */
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if(remove_item(&item))
            fprintf(stderr, "error removing\n");
        else
            printf("%lu consumed %d\n", tid, item);

        /* determining size for logging purpose */
        size = front > back ? (BUFFER_SIZE - front + back + 1) :
            front == -1 ? 0 : (back - front + 1);

        printf("buffer has %d items\n", size);

        /* release semaphores */
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }

    printf("%lu (consumer) exiting\n", tid);
    pthread_exit(0);
}

void *producer(void *param)
{
    buffer_item item;
    pthread_t tid = pthread_self();
    int sleep_dur;
    int size;

    while(run)
    {
        /* sleep for random duration */
        sleep_dur = rand() % 5;
        printf("%lu (producer) sleeping for %ds\n", tid, sleep_dur);
        sleep(sleep_dur);

        /* generate a random number */
        item = rand() % 1000;

        /* acquire semaphores */
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        if(insert_item(item))
            fprintf(stderr, "error inserting\n");
        else
            printf("%lu produced %d\n", tid, item);

        /* determining size for logging purpose */
        size = front > back ? (BUFFER_SIZE - front + back + 1) :
            front == -1 ? 0 : (back - front + 1);
        printf("buffer has %d items\n", size);

        /* release semaphores */
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    printf("%lu (producer) exiting\n", tid);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    // 1. get 3 command line arguments
    if(argc != 4)
    {
        printf("Requires 3 command line arguments: sleep duration, num producers, num consumers\n");
    }
    const int sleep_dur = strtol(argv[1], NULL, 10);
    const int num_producers = strtol(argv[2], NULL, 10);
    const int num_consumers = strtol(argv[3], NULL, 10);

    // 2. initialize buffer
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // 3. create producer threads
    pthread_t producer_tid[num_producers];
    int i;
    for(i = 0; i < num_producers; i++)
        pthread_create(&producer_tid[i], NULL, producer, NULL);

    // 4. create consumer threads
    pthread_t consumer_tid[num_consumers];
    for(i = 0; i < num_consumers; i++)
        pthread_create(&consumer_tid[i], NULL, consumer, NULL);

    // 5. sleep
    printf("\tmain thread sleeping\n");
    sleep(sleep_dur);

    // 6. exit
    run = 0;
    printf("\tmain thread wakes\n\ttelling child threads to finish and quit\n");

    for(i = 0; i < num_producers; i++)
        pthread_join(producer_tid[i], NULL);
    for(i = 0; i < num_consumers; i++)
        pthread_join(consumer_tid[i], NULL);
    return 0;
}

