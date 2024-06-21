#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
double **allocate_matrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double *));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void free_matrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to transpose a matrix
void transpose(double *matrix[], double *result[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

// Function to add two matrices
void add_matrices(double *matrix1[], double *matrix2[], double *result[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// Function to multiply two matrices
void multiply_matrices(double *matrix1[], double *matrix2[], double *result[], int rows1, int cols1, int cols2) {
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Function to print a matrix
void dump_matrix(double *matrix[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to reshape a matrix
void reshape_matrix(double *matrix[], double *result[], int rows, int cols, int new_rows, int new_cols) {
    if (rows * cols != new_rows * new_cols) {
        printf("Error: Cannot reshape matrix to desired dimensions\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    for (int i = 0; i < new_rows; i++) {
        for (int j = 0; j < new_cols; j++) {
            result[i][j] = matrix[index / cols][index % cols];
            index++;
        }
    }
}

int main() {
    int rows1 = 2, cols1 = 3;
    int rows2 = 2, cols2 = 3;
    int new_rows = 3, new_cols = 2;

    double **matrix1 = allocate_matrix(rows1, cols1);
    double **matrix2 = allocate_matrix(rows2, cols2);
    double **result = allocate_matrix(rows1, cols2);
    double **transposed = allocate_matrix(cols1, rows1);
    double **reshaped = allocate_matrix(new_rows, new_cols);

    // Initialize matrices
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix1[i][j] = i + j;
        }
    }

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = i * j;
        }
    }

    // Transpose matrix1
    transpose(matrix1, transposed, rows1, cols1);
    printf("Transposed matrix1:\n");
    dump_matrix(transposed, cols1, rows1);
    printf("\n");

    // Add matrix1 and matrix2
    add_matrices(matrix1, matrix2, result, rows1, cols1);
    printf("Matrix1 + Matrix2:\n");
    dump_matrix(result, rows1, cols1);
    printf("\n");

    // Multiply matrix1 and matrix2
    multiply_matrices(matrix1, matrix2, result, rows1, cols1, cols2);
    printf("Matrix1 * Matrix2:\n");
    dump_matrix(result, rows1, cols2);
    printf("\n");

    // Reshape matrix1
    reshape_matrix(matrix1, reshaped, rows1, cols1, new_rows, new_cols);
    printf("Reshaped matrix1:\n");
    dump_matrix(reshaped, new_rows, new_cols);
    printf("\n");

    // Free allocated memory
    free_matrix(matrix1, rows1);
    free_matrix(matrix2, rows2);
    free_matrix(result, rows1);
    free_matrix(transposed, cols1);
    free_matrix(reshaped, new_rows);

    return 0;
}
