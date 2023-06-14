#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


int state(n);
int philosophers[n] = {0, 1, 2, 3, 4};

pthread_mutex_t mutex;
pthread_cond_t cond[N];

// Function to test if the philosopher's neighbors are eating
void test(int philosopher)
{
    if (state[philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", philosopher + 1, LEFT + 1, philosopher + 1);
        printf("Philosopher %d is Eating\n", philosopher + 1);
        pthread_cond_signal(&cond[philosopher]);
    }
}

// Function to pick up forks
void pickUpForks(int philosopher)
{
    pthread_mutex_lock(&mutex);
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is Hungry\n", philosopher + 1);
    test(philosopher);
    pthread_mutex_unlock(&mutex);
    pthread_cond_wait(&cond[philosopher], &mutex);
}

// Function to put down forks
void putDownForks(int philosopher)
{
    pthread_mutex_lock(&mutex);
    state[philosopher] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", philosopher + 1, LEFT + 1, philosopher + 1);
    printf("Philosopher %d is thinking\n", philosopher + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

// Function for the philosopher threads
void* philosopherThread(void* arg)
{
    int philosopher = *(int*)arg;
    while (1) {
        sleep(1);
        pickUpForks(philosopher);
        sleep(0);
        putDownForks(philosopher);
    }
}

// Main function
int main()
{
    int i;
    pthread_t thread_id[N];
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++) {
        pthread_cond_init(&cond[i], NULL);
    }
    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopherThread, &philosophers[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < N; i++) {
        pthread_cond_destroy(&cond[i]);
    }
    return 0;
}

