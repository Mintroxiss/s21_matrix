#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <check.h>

#include "s21_matrix.h"

enum ERROR_CODES { KO, INCORRECT_MATRIX, CALCULATION_ERROR };

void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step);

void s21_suit_execution(Suite *suite, int *failed_count, char *suite_name);

#endif
