#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MATRIX_ERROR 1
#define CALC_ERROR 2

#define ACCURACY 1e-7

#define SUCCESS 1
#define FAILURE 0

#define ON 1
#define OFF 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создает матрицу
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Удаляет матрицу
void s21_remove_matrix(matrix_t *A);

// Сравнивает две матрицы (до 7-ми знаков после запятой):
// 1 - матрицы равны
// 0 - матрицы не равны
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Находит сумму матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Находит разность матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножает матрицу на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// Находит произведение матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирует матрицу
int s21_transpose(matrix_t *A, matrix_t *result);

// Создает матрицу алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Находит определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// Создает обратную матрицу
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Проверяет матрицу на корректность
int s21_matrix_error_checking(matrix_t *A);

// Сравнивает размерности матриц:
// 1 - равны
// 0 - не равны
int s21_matrix_size_equal(matrix_t *A, matrix_t *B);

// Возвращает значение минора для элемента i-ого ряда j-ого столбца
void s21_count_matrix_complements_element(int index_cross_out_row,
                                          int index_cross_out_column,
                                          matrix_t *A, double *value);

// Копирует матрицу A в матрицу B
void s21_copy_matrix(matrix_t *A, matrix_t *B);

// Проверяет матрицу на NULL-значения
int s21_matrix_unzero(matrix_t *A);

#endif
