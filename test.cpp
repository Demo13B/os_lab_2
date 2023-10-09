#include <pthread.h>
#include <iostream>

pthread_mutex_t mutex;
int sum;

void* incrementer(void* args) {
    pthread_mutex_lock(&mutex);
    ++sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main() {
    pthread_t threads[100];
    pthread_mutex_init(&mutex, NULL);

    for (size_t i = 0; i < 50; ++i) {
        pthread_create(&threads[i], NULL, incrementer, NULL);
    }

    for (size_t i = 0; i < 50; ++i) {
        pthread_join(threads[i], NULL);
    }

    std::cout << sum << std::endl;
}
