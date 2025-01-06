#include "../s21_matrix.h"

int s21_matrix_error_checking(matrix_t *A) {
  int error = OK;

  if (s21_matrix_unzero(A) || A->columns < 1 || A->rows < 1) {
    error = MATRIX_ERROR;
  }

  return error;
}

int s21_matrix_size_equal(matrix_t *A, matrix_t *B) {
  int result = FAILURE;

  if (A->columns == B->columns && A->rows == B->rows) {
    result = SUCCESS;
  }

  return result;
}

void s21_copy_matrix(matrix_t *A, matrix_t *B) {
  s21_create_matrix(A->rows, A->columns, B);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      B->matrix[i][j] = A->matrix[i][j];
    }
  }
}

int s21_matrix_unzero(matrix_t *A) {
  int error = OK;

  if (A == NULL || A->matrix == NULL) {
    error = MATRIX_ERROR;
  }

  return error;
}
