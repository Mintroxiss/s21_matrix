#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else {
    s21_create_matrix(A->columns, A->rows, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;
  if (s21_matrix_error_checking(A) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else if (A->rows == 1) {
    s21_create_matrix(A->rows, A->columns, result);
    result->matrix[0][0] = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double value = 0;
        s21_count_matrix_complements_element(i, j, A, &value);
        result->matrix[i][j] = pow(-1, (i + 1) + (j + 1)) * value;
      }
    }
  }

  return error;
}

void s21_count_matrix_complements_element(int index_cross_out_row,
                                          int index_cross_out_column,
                                          matrix_t *A, double *value) {
  matrix_t matrix_minor = {};
  s21_create_matrix(A->rows - 1, A->columns - 1, &matrix_minor);

  int minor_i = 0;
  int minor_j = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i != index_cross_out_row) {
      minor_j = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != index_cross_out_column) {
          matrix_minor.matrix[minor_i][minor_j] = A->matrix[i][j];
          minor_j++;
        }
      }
      minor_i++;
    }
  }

  s21_determinant(&matrix_minor, value);

  s21_remove_matrix(&matrix_minor);
}

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else {
    matrix_t copy_A;
    s21_copy_matrix(A, &copy_A);

    double det = 1.0;

    for (int i = 0; i < copy_A.rows; ++i) {
      // Находим максимальный элемент в текущем  столбце
      double mx = fabs(copy_A.matrix[i][i]);
      int id_x = i;
      for (int j = i + 1; j < copy_A.columns; ++j) {
        if (mx < fabs(copy_A.matrix[i][j])) {
          mx = fabs(copy_A.matrix[i][id_x = j]);
        }
      }

      // Переставляем строки если нужно
      if (id_x != i) {
        for (int j = i; j < copy_A.rows; ++j) {
          double t = copy_A.matrix[j][i];
          copy_A.matrix[j][i] = copy_A.matrix[j][id_x];
          copy_A.matrix[j][id_x] = t;
        }
        det = -det;
      }

      // Обнуляем элементы ниже главной диагонали
      for (int k = i + 1; k < copy_A.rows; ++k) {
        double t = copy_A.matrix[k][i] / copy_A.matrix[i][i];
        for (int j = i; j < copy_A.columns; ++j) {
          copy_A.matrix[k][j] -= copy_A.matrix[i][j] * t;
        }
      }
    }

    for (int i = 0; i < copy_A.rows; ++i) {
      det *= copy_A.matrix[i][i];
    }

    *result = det;

    s21_remove_matrix(&copy_A);
  }

  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (s21_matrix_error_checking(A) == MATRIX_ERROR || result == NULL) {
    error = MATRIX_ERROR;
  } else if (A->rows != A->columns) {
    error = CALC_ERROR;
  } else {
    double det = 0.0;
    error = s21_determinant(A, &det);
    if (det == 0.0) {
      error = CALC_ERROR;
    } else if (error == OK) {
      matrix_t calc_complements = {}, transp = {};

      error = s21_calc_complements(A, &calc_complements);
      error = s21_transpose(&calc_complements, &transp);
      error = s21_mult_number(&transp, 1.0 / det, result);

      s21_remove_matrix(&calc_complements);
      s21_remove_matrix(&transp);
    }
  }

  return error;
}
