#include <stdlib.h>

struct matrix {
    unsigned long int height;
    unsigned long int width;
    float *rows;
};

 int scalar_matrix_mult(float scalar_value, struct matrix *matrix);
 int matrix_matrix_mult(struct matrix *matrixA, struct matrix * matrixB, struct matrix * matrixC);


/**
 * Multiplies a matrix by a scalar value.
 * 
 * This function takes a scalar value and a matrix as input, and returns 1 if the
 * multiplication is successful, or 0 if the matrix is NULL or its rows are NULL.
 * 
 * @param scalar_value The scalar value to multiply the matrix by.
 * @param matrix The matrix to be multiplied.
 * @return 1 if the multiplication is successful, 0 otherwise.
 */
 int scalar_matrix_mult(float scalar_value, struct matrix *matrix){

    if (matrix == NULL || matrix->rows == NULL) {
        return 0;
    }
    int num_elements = (matrix->height * matrix->width);
    for(unsigned long int i = 0; i < num_elements; i++){
        matrix->rows[i] *= scalar_value;
    }
    return 1;

 }

/**
 * Performs matrix multiplication on two input matrices and stores the result in a third matrix.
 * 
 * This function takes three matrices as input: `matrix_a` and `matrix_b` are the input matrices to be multiplied,
 * and `matrix_c` is the output matrix where the result will be stored. The function returns 0 if the multiplication
 * is successful, or 1 if either of the input matrices is NULL, or if the number of columns in `matrix_a` does not
 * match the number of rows in `matrix_b`.
 * 
 * @param matrix_a The first input matrix.
 * @param matrix_b The second input matrix.
 * @param matrix_c The output matrix where the result will be stored.
 * @return 0 if the multiplication is successful, 1 otherwise.
 */
int matrix_matrix_mult(struct matrix *matrix_a, struct matrix *matrix_b, struct matrix *matrix_c)
{
    if (matrix_a == NULL || matrix_b == NULL) {
        return 1;
    }

    if (matrix_a->height != matrix_b->width) {
        return 1;
    }

    matrix_c->height = matrix_a->height;
    matrix_c->width = matrix_b->width;

    for (unsigned long int i = 0; i < matrix_a->height; ++i) {
        for (unsigned long int j = 0; j < matrix_b->width; ++j) {
            float sum = 0;
            for (unsigned long int k = 0; k < matrix_a->width; ++k) {
                sum += matrix_a->rows[i * matrix_a->width + k] * matrix_b->rows[k * matrix_b->width + j];
            }
            matrix_c->rows[i * matrix_c->width + j] = sum;
        }
    }

    return 0;
}
