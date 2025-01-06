#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = OK;

  if (result == NULL || columns < 1 || rows < 1) {
    error = MATRIX_ERROR;
  } else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }

    result->rows = rows;
    result->columns = columns;
  }

  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);

    A->matrix = NULL;

    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;

  int checking_of_matrix =
      s21_matrix_error_checking(A) + s21_matrix_error_checking(B) != OK;
  if (s21_matrix_size_equal(A, B) == FAILURE || checking_of_matrix) {
    result = FAILURE;
  }

  int stoper = OFF;
  for (int i = 0; i < A->rows && result && !stoper; i++) {
    for (int j = 0; j < A->columns && !stoper; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= ACCURACY) {
        result = FAILURE;
        stoper = ON;
      }
    }
  }

  return result;
}