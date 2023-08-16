#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OKEY 0
#define NOT_OKEY_MATRIX 1
#define NOT_OKEY_CALCULATION 2

// Структура матрицы
typedef struct matrix_struct {
  double **matrix;
  int rows;     // n
  int columns;  // m
} matrix_t;

// Функции по работе с матрицами
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Вспомогательные функции
int eqSizeMatrix(matrix_t *A, matrix_t *B);
void minorchik(matrix_t *minorMatrix, matrix_t *A, int n, int m);
int checkingMatrix(matrix_t *res);
void nullMatrix(matrix_t *A);

#endif  // SRC_S21_MATRIX_H