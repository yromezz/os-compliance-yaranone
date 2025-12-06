#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 3

typedef struct {
    int items[BUFFER_SIZE];
    int in, out;
    sem_t empty, full, mutex;
} buffer_t;

buffer_t buf;
int running = 1;

void printBuffer() {
    printf("Buffer: [");
    for(int i=0;i<BUFFER_SIZE;i++) printf("%d%s", buf.items[i], i<BUFFER_SIZE-1?", ":"");
    printf("]\n");
}

void *producer(void *arg) {
    int id = (int)arg; free(arg);
    while(running){
        int item = rand()%100;
        sem_wait(&buf.empty);
        sem_wait(&buf.mutex);
        buf.items[buf.in] = item;
        printf("Producer %d produced %d at %d\n", id, item, buf.in);
        buf.in = (buf.in+1)%BUFFER_SIZE;
        printBuffer();
        sem_post(&buf.mutex);
        sem_post(&buf.full);
        usleep((rand()%400+100)*1000);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = (int)arg; free(arg);
    while(running){
        sem_wait(&buf.full);
        sem_wait(&buf.mutex);
        int item = buf.items[buf.out];
        buf.items[buf.out] = 0;
        printf("Consumer %d consumed %d from %d\n", id, item, buf.out);
        buf.out = (buf.out+1)%BUFFER_SIZE;
        printBuffer();
        sem_post(&buf.mutex);
        sem_post(&buf.empty);
        usleep((rand()%400+100)*1000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    buf.in=buf.out=0;
    for(int i=0;i<BUFFER_SIZE;i++) buf.items[i]=0;
    sem_init(&buf.empty,0,BUFFER_SIZE);
    sem_init(&buf.full,0,0);
    sem_init(&buf.mutex,0,1);

    pthread_t prod[NUM_PRODUCERS], cons[NUM_CONSUMERS];
    for(int i=0;i<NUM_PRODUCERS;i++){int *id=malloc(sizeof(int));*id=i;pthread_create(&prod[i],0,producer,id);}
    for(int i=0;i<NUM_CONSUMERS;i++){int *id=malloc(sizeof(int));*id=i;pthread_create(&cons[i],0,consumer,id);}

    printf("Press Ctrl+C to stop\n");
    while(1) sleep(1);
    return 0;
}

