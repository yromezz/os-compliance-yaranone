#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdarg.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t chopsticks[NUM_PHILOSOPHERS];
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
int running = 1;

void safe_print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    pthread_mutex_lock(&print_mutex);
    vprintf(fmt, args);
    fflush(stdout);
    pthread_mutex_unlock(&print_mutex);
    va_end(args);
}

void think(int id) {
    safe_print("Philosopher %d is thinking\n", id);
    usleep((rand() % 300 + 200) * 1000);
}

void eat(int id) {
    safe_print("Philosopher %d is eating\n", id);
    usleep((rand() % 300 + 200) * 1000);
}

void pick_up_chopsticks_asymmetric(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    if (id % 2 == 1) {
        sem_wait(&chopsticks[left]);
        safe_print("Philosopher %d picked up left chopstick %d\n", id, left);

        sem_wait(&chopsticks[right]);
        safe_print("Philosopher %d picked up right chopstick %d\n", id, right);
    } else {
        sem_wait(&chopsticks[right]);
        safe_print("Philosopher %d picked up right chopstick %d\n", id, right);

        sem_wait(&chopsticks[left]);
        safe_print("Philosopher %d picked up left chopstick %d\n", id, left);
    }
}

void put_down_chopsticks(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    sem_post(&chopsticks[left]);
    sem_post(&chopsticks[right]);
    safe_print("Philosopher %d put down chopsticks %d and %d\n", id, left, right);
}

void *philosopher(void *arg) {
    int id = *(int *)arg;
    free(arg);

    while (running) {
        think(id);
        pick_up_chopsticks_asymmetric(id);
        eat(id);
        put_down_chopsticks(id);

        usleep((rand() % 200 + 100) * 1000);
    }
    return NULL;
}

void exit_handler(int sig) {
    running = 0;
    safe_print("\nStopping philosophers...\n");
}

int main() {
    srand(time(NULL));

    signal(SIGINT, exit_handler);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }

    while (running) {
        sleep(1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cancel(philosophers[i]);
        pthread_join(philosophers[i], NULL);
        sem_destroy(&chopsticks[i]);
    }

    safe_print("Cleanup complete. Exiting.\n");
    return 0;
}
