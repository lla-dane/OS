#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long long *fibonacci;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Array of condition variables, one for each Fibonacci number
pthread_cond_t *conditions;

// Function prototype for the thread
void *calculate_fibonacci(void *arg);

int main() {
    int n, i;

    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);

    // Allocate memory to store Fibonacci numbers and condition variables
    fibonacci = (long long *)malloc(n * sizeof(long long));
    conditions = (pthread_cond_t *)malloc(n * sizeof(pthread_cond_t));
    if (fibonacci == NULL || conditions == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Initialize the first two Fibonacci numbers and condition variables
    fibonacci[0] = 0;
    if (n > 1) {
        fibonacci[1] = 1;
    }
    for (i = 0; i < n; i++) {
        pthread_cond_init(&conditions[i], NULL);
    }

    pthread_t threads[n];

    // Create threads
    for (i = 2; i < n; i++) {
        int *arg = malloc(sizeof(*arg));
        if (arg == NULL) {
            perror("Failed to allocate memory for thread argument");
            free(fibonacci);
            free(conditions);
            exit(EXIT_FAILURE);
        }
        *arg = i;

        if (pthread_create(&threads[i], NULL, calculate_fibonacci, arg) != 0) {
            perror("Failed to create thread");
            free(arg);
        }

        printf("%ld ", threads[i]);
    }

    // Join threads
    for (i = 2; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the Fibonacci series
    printf("Fibonacci Series:\n");
    for (i = 0; i < n; i++) {
        printf("%lld ", fibonacci[i]);
    }
    printf("\n");

    // Clean up
    free(fibonacci);
    free(conditions);
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < n; i++) {
        pthread_cond_destroy(&conditions[i]);
    }

    return 0;
}

void *calculate_fibonacci(void *arg) {
    int n = *((int *)arg);\
    free(arg);

    pthread_mutex_lock(&mutex);

    while (fibonacci[n - 1] == 0 && n - 1 > 1) {
        pthread_cond_wait(&conditions[n - 1], &mutex);
    }

    fibonacci[n] = fibonacci[n - 1] + fibonacci[n - 2];

    // Signal the next thread that depends on this Fibonacci number
    pthread_cond_signal(&conditions[n]);
    
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}
