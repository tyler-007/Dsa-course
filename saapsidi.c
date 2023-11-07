#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to allocate memory for a 2D array
int** createMatrix(int M, int N) {
    int** matrix = (int**)malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
    }
    return matrix;
}

// Function to initialize the matrix with zeros
void initializeMatrix(int** matrix, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Function to read and set non-zero elements in the matrix
void setNonZeroElements(int** matrix, int M, int N, char* input) {
    char* token = strtok(input, ",");
    while (token != NULL) {
        int i, j;
        sscanf(token, "%d,%d", &i, &j);
        matrix[i][j] = 1;
        token = strtok(NULL, ",");
    }
}

// Function to check if a ladder exists starting at (i, j)
int hasLadder(int** matrix, int M, int N, int i, int j) {
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    for (int k = 0; k < 4; k++) {
        int x = i + dx[k];
        int y = j + dy[k];

        if (x >= 0 && x < M && y >= 0 && y < N && matrix[x][y] == 1) {
            return 1; // Ladder of length 2 or more found
        }
    }

    return 0; // No ladder found
}

// Function to find and print ladders in the matrix
void findAndPrintLadders(int** matrix, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 1 && hasLadder(matrix, M, N, i, j)) {
                printf("%d,%d\n", i, j);
            }
        }
    }
}

// Function to free memory allocated for the matrix
void freeMatrix(int** matrix, int M) {
    for (int i = 0; i < M; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int M, N;
    scanf("%d,%d", &M, &N);

    // Create and initialize the matrix
    int** matrix = createMatrix(M, N);
    initializeMatrix(matrix, M, N);

    // Read and set non-zero elements
    char input[100];
    scanf("%s", input);
    setNonZeroElements(matrix, M, N, input);

    // Find and print ladders
    findAndPrintLadders(matrix, M, N);

    // Free allocated memory
    freeMatrix(matrix, M);

    return 0;
}
