#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 3
#define NUM_PRODUCERS 1
#define NUM_CONSUMERS 1
#define NUM_ITEMS_TO_PRODUCE 4

typedef struct {
    int buffer[BUFFER_SIZE];
    int itemCount;
    int in;
    int out;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
} Buffer;

Buffer buffer;

void initializeBuffer() {
    buffer.itemCount = 0;
    buffer.in = 0;
    buffer.out = 0;
    pthread_mutex_init(&buffer.mutex, NULL);
    pthread_cond_init(&buffer.full, NULL);
    pthread_cond_init(&buffer.empty, NULL);
}

void produceItem(int item) {
    buffer.buffer[buffer.in] = item;
    buffer.in = (buffer.in + 1) % BUFFER_SIZE;
    buffer.itemCount++;
}

int consumeItem() {
    int item = buffer.buffer[buffer.out];
    buffer.out = (buffer.out + 1) % BUFFER_SIZE;
    buffer.itemCount--;
    return item;
}

void* producer(void* args) {
    int item;
    for (int i = 1; i <= NUM_ITEMS_TO_PRODUCE; i++) {
        pthread_mutex_lock(&buffer.mutex);
        while (buffer.itemCount == BUFFER_SIZE) {
            pthread_cond_wait(&buffer.empty, &buffer.mutex);
        }
        item = i;
        produceItem(item);
        printf("Produced item %d\n", item);
        if (buffer.itemCount == BUFFER_SIZE) {
            printf("Buffer is FULL\n");
        }
        pthread_cond_signal(&buffer.full);
        pthread_mutex_unlock(&buffer.mutex);
    }
    return NULL;
}

void* consumer(void* args) {
    int item;
    pthread_mutex_lock(&buffer.mutex);
    while (buffer.itemCount == 0) {
        pthread_cond_wait(&buffer.full, &buffer.mutex);
    }
    item = consumeItem();
    printf("Consumed item %d\n", item);
    if (buffer.itemCount == 0) {
        printf("Buffer is EMPTY\n");
    }
    pthread_cond_signal(&buffer.empty);
    pthread_mutex_unlock(&buffer.mutex);
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    initializeBuffer();

    pthread_create(&producers[0], NULL, producer, NULL);
    pthread_create(&consumers[0], NULL, consumer, NULL);

    pthread_join(producers[0], NULL);
    pthread_join(consumers[0], NULL);

    pthread_mutex_destroy(&buffer.mutex);
    pthread_cond_destroy(&buffer.full);
    pthread_cond_destroy(&buffer.empty);

    return 0;
}