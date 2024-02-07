#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long *fibonacci;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t *conditions;

// Structure to hold thread data
typedef struct {
    int index; // Index of the Fibonacci number to calculate
    int id;    // Simple numeric ID for the thread
} thread_data;

void *calculate_fibonacci(void *arg);

int main() {
    int n, i;

    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);

    fibonacci = (long long *)malloc(n * sizeof(long long));
    conditions = (pthread_cond_t *)malloc(n * sizeof(pthread_cond_t));
    if (fibonacci == NULL || conditions == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    fibonacci[0] = 0;
    if (n > 1) {
        fibonacci[1] = 1;
    }
    for (i = 0; i < n; i++) {
        pthread_cond_init(&conditions[i], NULL);
    }

    pthread_t threads[n];
    thread_data data[n]; // Array of thread_data structures

    for (i = 2; i < n; i++) {
        data[i].index = i;
        data[i].id = i; // Assign a simple numeric ID equal to the index

        if (pthread_create(&threads[i], NULL, calculate_fibonacci, &data[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    for (i = 2; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Fibonacci Series:\n");
    for (i = 0; i < n; i++) {
        printf("%lld ", fibonacci[i]);
    }
    printf("\n");

    free(fibonacci);
    free(conditions);
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < n; i++) {
        pthread_cond_destroy(&conditions[i]);
    }

    return 0;
}

void *calculate_fibonacci(void *arg) {
    thread_data *data = (thread_data *)arg;
    int n = data->index;

    pthread_mutex_lock(&mutex);

    while (fibonacci[n - 1] == 0 && n - 1 > 1) {
        pthread_cond_wait(&conditions[n - 1], &mutex);
    }

    fibonacci[n] = fibonacci[n - 1] + fibonacci[n - 2];
    printf("Thread %d calculated fibonacci[%d] = %lld\n", data->id, n, fibonacci[n]);

    pthread_cond_signal(&conditions[n]);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
