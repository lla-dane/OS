#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Array to store Fibonacci numbers
long long *fibonacci;

// Function prototype for the thread
void *calculate_fibonacci(void *arg);

int main() {
    int n, i;

    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);

    // Allocate memory to store Fibonacci numbers
    fibonacci = (long long *)malloc(n * sizeof(long long));
    if (fibonacci == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    // Initialize the first two Fibonacci numbers
    fibonacci[0] = 0;
    if (n > 1) {
        fibonacci[1] = 1;
    }

    // Create and execute threads sequentially
    for (i = 2; i < n; i++) {
        pthread_t thread;
        int *arg = malloc(sizeof(*arg));
        if (arg == NULL) {
            perror("Failed to allocate memory for thread argument");
            free(fibonacci);
            exit(EXIT_FAILURE);
        }
        *arg = i;

        if (pthread_create(&thread, NULL, calculate_fibonacci, arg) != 0) {
            perror("Failed to create thread");
            free(arg);
            continue;
        }

        printf("%ld ", thread );
        // Wait for the created thread to complete
        pthread_join(thread, NULL);
    }

    // Print the Fibonacci series
    printf("Fibonacci Series:\n");
    for (i = 0; i < n; i++) {
        printf("%lld ", fibonacci[i]);
    }
    printf("\n");

    // Clean up
    free(fibonacci);

    return 0;
}

void *calculate_fibonacci(void *arg) {
    int n = *((int *)arg);
    free(arg);

    fibonacci[n] = fibonacci[n - 1] + fibonacci[n - 2];

    pthread_exit(NULL);
}
