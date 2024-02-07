#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3 // Number of rows in A and C
#define K 2 // Number of columns in A and rows in B
#define N 3 // Number of columns in B and C

// Modify matrix C to include thread ID
typedef struct {
    int value;       // Result of multiplication
    unsigned long threadID; // Thread ID
} MatrixElement;

int A[M][K] = {{1, 2}, {3, 4}, {5, 6}};
int B[K][N] = {{7, 8, 9}, {10, 11, 12}};
MatrixElement C[M][N]; // Updated matrix C definition

typedef struct {
    int row;
    int col;
} Position;

void* multiply(void* arg) {
    Position position = *(Position*) arg;
    int sum = 0;
    for (int k = 0; k < K; ++k) {
        sum += A[position.row][k] * B[k][position.col];
    }

    // Save the result and the thread ID in matrix C
    C[position.row][position.col].value = sum;
    C[position.row][position.col].threadID = (unsigned long)pthread_self();

    pthread_exit(0);
}

int main() {
    pthread_t threads[M][N];
    Position positions[M][N];

    // Create M*N worker threads
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            positions[i][j].row = i;
            positions[i][j].col = j;
            pthread_create(&threads[i][j], NULL, multiply, (void*)&positions[i][j]);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }

    // Print the result matrix C along with thread IDs
    printf("Matrix C (Result) with Thread IDs:\n");
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("[%d, TID: %lu] ", C[i][j].value, C[i][j].threadID);
        }
        printf("\n");
    }

    return 0;
}
