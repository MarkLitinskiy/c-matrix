#include <check.h>

#include "s21_matrix.h"

#define MAX_DOUBLE 1.79769e+308
#define MIN_DOUBLE 2.22507e-308

START_TEST(s21_create_matrix_1) {  // на корректное создание
  matrix_t A = {0};
  matrix_t B = {0};
  ck_assert_int_eq(0, s21_create_matrix(3, 3, &A));
  ck_assert_int_eq(3, A.rows);
  ck_assert_int_eq(3, A.columns);
  ck_assert_int_eq(0, s21_create_matrix(1000, 1001, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_create_matrix_2) {  // на некорректное создание
  matrix_t A = {0};
  matrix_t B = {0};
  ck_assert_int_eq(1, s21_create_matrix(-5, 3, &A));
  ck_assert_int_eq(1, s21_create_matrix(0, 3, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_1) {  // Не созданные матрицы
  matrix_t A = {0};
  matrix_t B = {0};
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_2) {  // Заполненные нулями матрицы
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_3) {  // Неравные матрицы
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[1][1] = 26;
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[1][1] = 2.0000020f;
  B.matrix[1][1] = 2.0000002f;
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[1][1] = 2.0000020f;
  B.matrix[1][1] = 2.0000020f;
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_6) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[1][1] = MIN_DOUBLE;
  B.matrix[1][1] = MIN_DOUBLE;
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_7) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[1][1] = MAX_DOUBLE;
  B.matrix[1][1] = MAX_DOUBLE;
  ck_assert_int_eq(1, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_8) {  // Матрицы разного размера
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 4, &B);
  ck_assert_int_eq(0, s21_eq_matrix(&A, &B));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_remove_matrix_1) {
  int result = 0;
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    result = 1;
  }
  ck_assert_int_eq(0, result);
}
END_TEST

START_TEST(s21_sum_matrix_1) {  // Матрицы разного размера
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 4, &B);
  ck_assert_int_eq(2, s21_sum_matrix(&A, &B, &C));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  int m = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  m = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B.matrix[i][j] = m;
      m--;
    }
  }
  ck_assert_int_eq(0, s21_sum_matrix(&A, &B, &C));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_ldouble_eq_tol(0, C.matrix[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_3) {
  int m = 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  m = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B.matrix[i][j] = m;
      m++;
    }
  }
  m = 1;
  ck_assert_int_eq(0, s21_sum_matrix(&A, &B, &C));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_ldouble_eq_tol(m * 2, C.matrix[i][j], 1e-7);
      m++;
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sum_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  B.matrix = NULL;
  B.rows = 2;
  B.columns = 3;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(1, s21_sum_matrix(&A, &B, &C));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sum_matrix_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C;
  int rows_A = 2, columns_A = 3;
  B.rows = -1, B.columns = 3;
  s21_create_matrix(rows_A, columns_A, &A);
  ck_assert_int_eq(1, s21_sum_matrix(&A, &B, &C));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sum_matrix_6) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t result = {NULL, 0, 0};
  matrix_t result_full = {NULL, 0, 0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result_full);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = j + 1 + 910.0000002;
      B.matrix[i][j] = j + 1 + 4.0000002;
      result_full.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], result_full.matrix[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_full);
}
END_TEST

START_TEST(s21_sub_matrix_1) {  // Матрицы разного размера
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 4, &B);
  ck_assert_int_eq(2, s21_sub_matrix(&A, &B, &C));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  int m = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m++;
    }
  }
  m = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B.matrix[i][j] = m;
      m++;
    }
  }
  ck_assert_int_eq(0, s21_sub_matrix(&A, &B, &C));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_ldouble_eq_tol(0, C.matrix[i][j], 1e-7);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_3) {
  int m = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = m;
      m--;
    }
  }
  m = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B.matrix[i][j] = m;
      m++;
    }
  }
  m = 0;
  ck_assert_int_eq(0, s21_sub_matrix(&A, &B, &C));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_ldouble_eq_tol(m * 2, C.matrix[i][j], 1e-7);
      m--;
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  B.matrix = NULL;
  B.rows = 2;
  B.columns = 3;
  s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(1, s21_sub_matrix(&A, &B, &C));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sub_matrix_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  int rows_A = 2, columns_A = 3;
  B.rows = -1, B.columns = 3;
  s21_create_matrix(rows_A, columns_A, &A);
  ck_assert_int_eq(1, s21_sub_matrix(&A, &B, &C));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_sub_matrix_6) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t result = {NULL, 0, 0};
  matrix_t result_full = {NULL, 0, 0};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  s21_create_matrix(2, 2, &result_full);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = j + 1 + 910.0000002;
      B.matrix[i][j] = j + 1 + 4.0000002;
      result_full.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(result.matrix[i][j], result_full.matrix[i][j]);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_full);
}
END_TEST

START_TEST(s21_mult_number_1) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  double res = 5.123f;
  s21_create_matrix(4, 3, &A);
  s21_create_matrix(4, 3, &C);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 1.21030120f;
      C.matrix[i][j] = res * A.matrix[i][j];
    }
  }

  ck_assert_int_eq(s21_mult_number(&A, res, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_number_2) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  double res = 6.3456f;
  s21_create_matrix(6, 4, &A);
  s21_create_matrix(6, 4, &C);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 7.28310420f;
      C.matrix[i][j] = res * A.matrix[i][j];
    }
  }
  A.rows = -1;
  ck_assert_int_eq(s21_mult_number(&A, res, &B), 1);
  A.rows = 6;
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_number_3) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  double res = 0;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &C);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 7;
      C.matrix[i][j] = res * A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, res, &B), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_number_4) {
  matrix_t A = {0};
  matrix_t result = {0};
  int rows_A = -6, columns_A = 6;
  s21_create_matrix(rows_A, columns_A, &A);
  ck_assert_int_eq(1, s21_mult_number(&A, 4, &result));
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_mult_number_5) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  double res = MAX_DOUBLE;
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &C);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 7;
      C.matrix[i][j] = res * A.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, res, &B), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  s21_create_matrix(4, 3, &A);
  s21_create_matrix(4, 3, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_3) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t res = {NULL, 0, 0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 6;
  A.matrix[2][1] = 7;
  A.matrix[2][2] = 8;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 1;
  B.matrix[0][2] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;
  B.matrix[1][2] = 5;
  B.matrix[2][0] = 6;
  B.matrix[2][1] = 7;
  B.matrix[2][2] = 8;

  C.matrix[0][0] = 15;
  C.matrix[0][1] = 18;
  C.matrix[0][2] = 21;
  C.matrix[1][0] = 42;
  C.matrix[1][1] = 54;
  C.matrix[1][2] = 66;
  C.matrix[2][0] = 69;
  C.matrix[2][1] = 90;
  C.matrix[2][2] = 111;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), 0);

  ck_assert_int_eq(s21_eq_matrix(&C, &res), 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_4) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  s21_create_matrix(5, 0, &A);
  s21_create_matrix(7, 9, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &C), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mult_matrix_5) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(2, 3, &A);

  s21_create_matrix(2, 2, &B);

  res = s21_mult_matrix(&A, &B, &C);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_transpose_1) {
  matrix_t A = {0};
  matrix_t res = {0};
  A.matrix = NULL;
  ck_assert_int_eq(s21_transpose(&A, &res), 1);
}
END_TEST

START_TEST(s21_transpose_2) {
  matrix_t A = {NULL, 0, 0};
  matrix_t res = {NULL, 0, 0};
  s21_create_matrix(3, 5, &A);
  ck_assert_int_eq(s21_transpose(&A, &res), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_transpose_3) {
  matrix_t A = {NULL, 0, 0};
  matrix_t result = {NULL, 0, 0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 6;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 9;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 6;
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;
  A.matrix[0][1] = 4;
  A.matrix[1][1] = 5;
  A.matrix[2][1] = 6;
  A.matrix[0][2] = 7;
  A.matrix[1][2] = 8;
  A.matrix[2][2] = 9;
  ck_assert_int_eq(0, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(0, result, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_2) {
  int res = 0;
  double determ = 0;
  matrix_t A = {NULL, 0, 0};

  res = s21_determinant(&A, &determ);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_3) {
  matrix_t A = {0};
  double result = 0;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 5;
  A.matrix[1][0] = 1;
  A.matrix[2][0] = 0;
  A.matrix[0][1] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][1] = 5;
  A.matrix[0][2] = 1;
  A.matrix[1][2] = 6;
  A.matrix[2][2] = 9;
  ck_assert_int_eq(0, s21_determinant(&A, &result));
  ck_assert_ldouble_eq_tol(8, result, 1e-7);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_4) {
  double result = 0;
  matrix_t A = {0};
  s21_create_matrix(1, 2, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  s21_calc_complements(&A, &B);

  s21_create_matrix(3, 3, &C);

  C.matrix[0][0] = 0;
  C.matrix[0][1] = 10;
  C.matrix[0][2] = -20;
  C.matrix[1][0] = 4;
  C.matrix[1][1] = -14;
  C.matrix[1][2] = 8;
  C.matrix[2][0] = -8;
  C.matrix[2][1] = 2;
  C.matrix[2][2] = 4;

  ck_assert_int_eq(0, s21_eq_matrix(&C, &B));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t res = {NULL, 0, 0};
  s21_create_matrix(2, 3, &A);

  s21_create_matrix(3, 2, &res);

  ck_assert_int_eq(s21_calc_complements(&A, &B), 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t res = {NULL, 0, 0};
  s21_create_matrix(2, 3, &A);

  s21_create_matrix(3, 2, &res);

  A.rows = 0;
  ck_assert_int_eq(s21_calc_complements(&A, &B), 1);

  A.rows = 2;

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  res = s21_calc_complements(&A, &B);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t matrixA = {0};
  matrix_t result = {0};
  matrixA.matrix = NULL;
  ck_assert_int_eq(1, s21_inverse_matrix(&matrixA, &result));
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t matrixA = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &matrixA);
  matrixA.matrix[0][0] = 1;
  matrixA.matrix[1][0] = 2;
  matrixA.matrix[2][0] = 3;
  matrixA.matrix[0][1] = 4;
  matrixA.matrix[1][1] = 5;
  matrixA.matrix[2][1] = 6;
  matrixA.matrix[0][2] = 7;
  matrixA.matrix[1][2] = 8;
  matrixA.matrix[2][2] = 9;
  ck_assert_int_eq(2, s21_inverse_matrix(&matrixA, &result));
  s21_remove_matrix(&matrixA);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  int res = 0;
  matrix_t A = {NULL, 0, 0};
  matrix_t B = {NULL, 0, 0};
  matrix_t result = {NULL, 0, 0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;

  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = -1.0;
  B.matrix[0][2] = 1.0;
  B.matrix[1][0] = -38.0;
  B.matrix[1][1] = 41.0;
  B.matrix[1][2] = -34.0;
  B.matrix[2][0] = 27.0;
  B.matrix[2][1] = -29.0;
  B.matrix[2][2] = 24.0;
  res = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(res, 0);

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      ck_assert_double_eq(B.matrix[i][j], result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 2, &A);

  res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21create_matrix(void) {
  Suite *suite = suite_create("ts_s21_create_matrix");
  TCase *test_case = tcase_create("tcs_s21_create_matrix");
  tcase_add_test(test_case, s21_create_matrix_1);
  tcase_add_test(test_case, s21_create_matrix_2);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21remove_matrix(void) {
  Suite *suite = suite_create("ts_s21_remove_matrix");
  TCase *test_case = tcase_create("tcs_s21_remove_matrix");
  tcase_add_test(test_case, s21_remove_matrix_1);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21eq_matrix(void) {
  Suite *suite = suite_create("ts_s21_eq_matrix");
  TCase *test_case = tcase_create("tcs_s21_eq_matrix");
  tcase_add_test(test_case, s21_eq_matrix_1);
  tcase_add_test(test_case, s21_eq_matrix_2);
  tcase_add_test(test_case, s21_eq_matrix_3);
  tcase_add_test(test_case, s21_eq_matrix_4);
  tcase_add_test(test_case, s21_eq_matrix_5);
  tcase_add_test(test_case, s21_eq_matrix_6);
  tcase_add_test(test_case, s21_eq_matrix_7);
  tcase_add_test(test_case, s21_eq_matrix_8);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21sum_matrix(void) {
  Suite *suite = suite_create("ts_s21_sum_matrix");
  TCase *test_case = tcase_create("tcs_s21_sum_matrix");
  tcase_add_test(test_case, s21_sum_matrix_1);
  tcase_add_test(test_case, s21_sum_matrix_2);
  tcase_add_test(test_case, s21_sum_matrix_3);
  tcase_add_test(test_case, s21_sum_matrix_4);
  tcase_add_test(test_case, s21_sum_matrix_5);
  tcase_add_test(test_case, s21_sum_matrix_6);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21sub_matrix(void) {
  Suite *suite = suite_create("ts_s21_sub_matrix");
  TCase *test_case = tcase_create("tcs_s21_sub_matrix");
  tcase_add_test(test_case, s21_sub_matrix_1);
  tcase_add_test(test_case, s21_sub_matrix_2);
  tcase_add_test(test_case, s21_sub_matrix_3);
  tcase_add_test(test_case, s21_sub_matrix_4);
  tcase_add_test(test_case, s21_sub_matrix_5);
  tcase_add_test(test_case, s21_sub_matrix_6);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21mult_number_matrix(void) {
  Suite *suite = suite_create("ts_s21_mult_number_matrix");
  TCase *test_case = tcase_create("tcs_s21_mult_number_matrix");
  tcase_add_test(test_case, s21_mult_number_1);
  tcase_add_test(test_case, s21_mult_number_2);
  tcase_add_test(test_case, s21_mult_number_3);
  tcase_add_test(test_case, s21_mult_number_4);
  tcase_add_test(test_case, s21_mult_number_5);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21mult_mult_matrix(void) {
  Suite *suite = suite_create("ts_s21_mult_matrix");
  TCase *test_case = tcase_create("tcs_s21_mult_matrix");
  tcase_add_test(test_case, s21_mult_matrix_1);
  tcase_add_test(test_case, s21_mult_matrix_2);
  tcase_add_test(test_case, s21_mult_matrix_3);
  tcase_add_test(test_case, s21_mult_matrix_4);
  tcase_add_test(test_case, s21_mult_matrix_5);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21transpose(void) {
  Suite *suite = suite_create("ts_s21_transpose");
  TCase *test_case = tcase_create("tcs_s21_transpose");
  tcase_add_test(test_case, s21_transpose_1);
  tcase_add_test(test_case, s21_transpose_2);
  tcase_add_test(test_case, s21_transpose_3);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21determinant(void) {
  Suite *suite = suite_create("ts_s21_determinant");
  TCase *test_case = tcase_create("tcs_s21_determinant");
  tcase_add_test(test_case, s21_determinant_1);
  tcase_add_test(test_case, s21_determinant_2);
  tcase_add_test(test_case, s21_determinant_3);
  tcase_add_test(test_case, s21_determinant_4);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21calc_complements(void) {
  Suite *suite = suite_create("ts_s21_calc_complements");
  TCase *test_case = tcase_create("tcs_s21_calc_complements");
  tcase_add_test(test_case, s21_calc_complements_1);
  tcase_add_test(test_case, s21_calc_complements_2);
  tcase_add_test(test_case, s21_calc_complements_3);
  tcase_add_test(test_case, s21_calc_complements_4);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *s21inverse_matrix(void) {
  Suite *suite = suite_create("ts_s21_inverse_matrix");
  TCase *test_case = tcase_create("tcs_s21_inverse_matrix");
  tcase_add_test(test_case, s21_inverse_matrix_1);
  tcase_add_test(test_case, s21_inverse_matrix_2);
  tcase_add_test(test_case, s21_inverse_matrix_3);
  tcase_add_test(test_case, s21_inverse_matrix_4);
  suite_add_tcase(suite, test_case);

  return suite;
}

int main() {
  Suite *test_suites[] = {
      s21create_matrix(),    s21remove_matrix(),  s21eq_matrix(),
      s21sum_matrix(),       s21sub_matrix(),     s21mult_number_matrix(),
      s21mult_mult_matrix(), s21transpose(),      s21determinant(),
      s21calc_complements(), s21inverse_matrix(), NULL};
  int failed = 0;

  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}