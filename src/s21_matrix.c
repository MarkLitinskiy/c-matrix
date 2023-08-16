#include "s21_matrix.h"
#define ROWS 3
#define COLUMNS 3

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    res = 1;
  } else {
    nullMatrix(result);
    result->matrix =
        (double **)malloc(rows * sizeof(double *));  // Выделение памяти
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
    }
    if (result != NULL && result->matrix != NULL) {
      result->rows = rows;
      result->columns = columns;
      for (int i = 0; i < rows; i++) {  // заполнение массива нулями
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = 0;
        }
      }
    } else {
      res = NOT_OKEY_MATRIX;
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {  // очистка места
      if (A->matrix[i]) free(A->matrix[i]);
    }
    free(A->matrix);
    nullMatrix(A);  // зануляем
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int countRowsColums = SUCCESS;
  if (eqSizeMatrix(A, B) == NOT_OKEY_CALCULATION || A->matrix == NULL ||
      B->matrix == NULL)  // проверка одинакого ли размера матрицы
    countRowsColums = FAILURE;
  if (countRowsColums == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((int)(A->matrix[i][j] * pow(10, 7)) !=
            (int)(B->matrix[i][j] *
                  pow(10, 7))) {  // сравниваю точность 7 знаков
          countRowsColums = FAILURE;
        }
      }
    }
  }
  return countRowsColums;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  nullMatrix(result);
  int res = OKEY;
  if (checkingMatrix(A) == 1 || checkingMatrix(B) == 1) {
    res = NOT_OKEY_MATRIX;
  } else {
    if (eqSizeMatrix(A, B) == OKEY &&
        res == OKEY) {  // проверка одинакого ли размера матрицы
      if (s21_create_matrix(A->rows, A->columns, result) == OKEY) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      } else {
        res = NOT_OKEY_MATRIX;
      }
    } else {
      res = NOT_OKEY_CALCULATION;
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  nullMatrix(result);
  int res = OKEY;
  if (checkingMatrix(A) == 1 || checkingMatrix(B) == 1) {
    res = NOT_OKEY_MATRIX;
  } else {
    if (eqSizeMatrix(A, B) == OKEY &&
        res == OKEY) {  // проверка одинакого ли размера матрицы
      if (s21_create_matrix(A->rows, A->columns, result) == OKEY) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      } else {
        res = NOT_OKEY_MATRIX;
      }
    } else {
      res = NOT_OKEY_CALCULATION;
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  nullMatrix(result);
  int res = OKEY;
  if (checkingMatrix(A) == 1) res = NOT_OKEY_MATRIX;
  if (res == OKEY) {
    if (number != NAN || number != INFINITY) {
      if (s21_create_matrix(A->rows, A->columns, result) == OKEY) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] * number;
            if (result->matrix[i][j] == INFINITY) res = NOT_OKEY_CALCULATION;
          }
        }
      } else {
        res = NOT_OKEY_MATRIX;
      }
    } else {
      res = NOT_OKEY_CALCULATION;
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  nullMatrix(result);
  int res = OKEY;
  if (checkingMatrix(A) == 1 || checkingMatrix(B) == 1) res = NOT_OKEY_MATRIX;
  if (res == OKEY) {
    if ((A->columns == B->rows)) {
      if (s21_create_matrix(A->rows, B->columns, result) == OKEY) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = 0;
            for (int k = 0; k < A->columns; k++) {
              result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
              if (result->matrix[i][j] == INFINITY) res = NOT_OKEY_CALCULATION;
            }
          }
        }
      } else {
        res = NOT_OKEY_MATRIX;
      }
    } else {
      res = NOT_OKEY_CALCULATION;  // проверка на A = m × k и B = k × n (у
                                   // первой матрицы строк больше, чем у второй)
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OKEY;
  if (checkingMatrix(A) == 1) res = NOT_OKEY_MATRIX;
  if (res == OKEY) {
    if (s21_create_matrix(A->columns, A->rows, result) == OKEY) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      res = NOT_OKEY_MATRIX;
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  nullMatrix(result);
  int res = 0;
  double min = 0;
  if (checkingMatrix(A) == 1 || result == NULL) res = NOT_OKEY_MATRIX;
  if (res == 0) {
    if (A->columns == A->rows) {  // проверка матрицы на квадратность
      if (s21_create_matrix(A->columns, A->rows, result) == OKEY) {
        if (A->columns == 1) {  // Если матрица из одного элемента
          result->matrix[0][0] = A->matrix[0][0];
        } else {
          matrix_t current = {0};
          res = s21_create_matrix(A->rows - 1, A->columns - 1,
                                  &current);  // временная матрица для минора
          if (res == 0) {
            for (int i = 0; i < result->rows; i++) {
              for (int j = 0; j < result->columns; j++) {
                min = 0;
                minorchik(
                    &current, A, j,
                    i);  // создаём матрицу с вырезанной строчкой и столбцом
                s21_determinant(&current, &min);
                result->matrix[i][j] = min * pow(-1, i + j);
              }
            }
            s21_remove_matrix(&current);
          }
        }
      } else {
        res = NOT_OKEY_MATRIX;
      }
    } else {
      res = NOT_OKEY_CALCULATION;
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = OKEY;
  int znak = -1;
  double det = 0;
  *result = 0;
  if (checkingMatrix(A) == 1) res = NOT_OKEY_MATRIX;
  if (res == OKEY) {
    if (A->columns == A->rows) {  // проверка матрицы на квадратность
      if (A->columns == 1)
        *result = A->matrix[0][0];  // если матрица из одного элемента
      if (A->columns == 2)  // если матрица из двух элементов
        *result = (A->matrix[0][0] * A->matrix[1][1]) -
                  (A->matrix[0][1] * A->matrix[1][0]);
      if (A->columns >= 3) {
        matrix_t current = {0};
        res = s21_create_matrix(A->rows - 1, A->columns - 1, &current);
        for (int i = 0; i < A->columns; i++) {  // определитель по первой строке
          det = 0;
          if (res == 0) {
            minorchik(&current, A, i,
                      0);  // создаём матрицу с вырезанной строчкой и столбцом
            znak = znak * (-1);
            s21_determinant(&current, &det);
            *result += znak * A->matrix[0][i] * det;
          }
        }
        s21_remove_matrix(&current);
      }
    } else {
      res = NOT_OKEY_CALCULATION;
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  nullMatrix(result);
  int res = OKEY;
  double det = 0;
  // Блок проверочек
  if (checkingMatrix(A) == 1 || result == NULL) {
    res = NOT_OKEY_MATRIX;
  } else {
    if (A->columns != A->rows) {  // проверка матрицы на квадратность
      res = NOT_OKEY_CALCULATION;
    } else {
      s21_determinant(A, &det);
      if (det == 0 ||
          fabs(det) < 1e-7) {  // Проверка на то что определитель не равен 0
        res = NOT_OKEY_CALCULATION;
      } else {
        if (s21_create_matrix(A->columns, A->rows, result) != OKEY) {
          res = NOT_OKEY_MATRIX;
        }
      }
    }
  }
  if (res == OKEY) {
    if (A->columns == 1) {  // Если матрица из одного элемента
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else {
      matrix_t algebraDop = {0};
      matrix_t result2 = {0};
      if (s21_calc_complements(A, &algebraDop) == OKEY &&
          s21_transpose(&algebraDop, &result2) == OKEY) {
        for (int i = 0; i < result->rows; i++) {
          for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = result2.matrix[i][j] * (1 / det);
          }
        }
      } else {
        res = NOT_OKEY_MATRIX;
      }
      s21_remove_matrix(&algebraDop);
      s21_remove_matrix(&result2);
    }
  }
  return res;
}

int eqSizeMatrix(matrix_t *A, matrix_t *B) {
  int result = 0;
  if (A->rows != B->rows || A->columns != B->columns) {
    result = 2;
  }
  return result;
}

void minorchik(matrix_t *minorchikMatrix, matrix_t *A, int n,
               int m) {  // n и m значение столбца и строки, которые вырезаются
  int ki = 0;
  int kj = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i == m || j == n) continue;
      minorchikMatrix->matrix[ki][kj] = A->matrix[i][j];
      kj++;
    }
    if (i == m) continue;
    kj = 0;
    ki++;
  }
}

int checkingMatrix(matrix_t *res) {
  int result = 0;
  if (res == NULL || res->matrix == NULL || res->rows < 1 || res->columns < 1) {
    result = 1;
  }
  return result;
}

void nullMatrix(matrix_t *A) {
  if (A != NULL) {
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}