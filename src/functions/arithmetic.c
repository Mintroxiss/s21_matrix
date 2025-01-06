#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR ||
      s21_matrix_error_checking(B) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else if (!s21_matrix_size_equal(A, B)) {
    error = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) {
          error = CALC_ERROR;
        }
      }
    }
  }

  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR ||
      s21_matrix_error_checking(B) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else if (!s21_matrix_size_equal(A, B)) {
    error = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) {
          error = CALC_ERROR;
        }
      }
    }
  }

  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (!isfinite(result->matrix[i][j])) {
          error = CALC_ERROR;
        }
      }
    }
  }

  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR ||
      s21_matrix_error_checking(B) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else if (A->columns != B->rows) {
    error = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          if (!isfinite(result->matrix[i][j])) {
            error = CALC_ERROR;
          }
        }
      }
    }
  }

  return error;
}
