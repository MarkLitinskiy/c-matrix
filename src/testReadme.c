#include "s21_matrix.h"

int main() {
  matrix_t one = {0};
  matrix_t two = {0};
  matrix_t three = {0};
  matrix_t four = {0};
  matrix_t five = {0};
  matrix_t six = {0};
  matrix_t result1 = {0};
  matrix_t result2 = {0};
  matrix_t result3 = {0};
  matrix_t result4 = {0};
  matrix_t result5 = {0};
  matrix_t result6 = {0};
  matrix_t result7 = {0};

  s21_create_matrix(3, 3, &one);
  s21_create_matrix(3, 3, &two);
  s21_create_matrix(3, 2, &three);
  s21_create_matrix(2, 3, &four);
  s21_create_matrix(3, 3, &five);
  s21_create_matrix(4, 4, &six);

  six.matrix[0][0] = 1;
  six.matrix[0][1] = 2;
  six.matrix[0][2] = 3;
  six.matrix[0][3] = 4;
  six.matrix[1][0] = 5;
  six.matrix[1][1] = 6;
  six.matrix[1][2] = 7;
  six.matrix[1][3] = 8;
  six.matrix[2][0] = 9;
  six.matrix[2][1] = 1;
  six.matrix[2][2] = 2;
  six.matrix[2][3] = 3;
  six.matrix[3][0] = 4;
  six.matrix[3][1] = 5;
  six.matrix[3][2] = 6;
  six.matrix[3][3] = 7;

  one.matrix[0][0] = 1;
  one.matrix[0][1] = 2;
  one.matrix[0][2] = 3;
  one.matrix[1][0] = 4;
  one.matrix[1][1] = 5;
  one.matrix[1][2] = 6;
  one.matrix[2][0] = 7;
  one.matrix[2][1] = 8;
  one.matrix[2][2] = 9;

  two.matrix[0][0] = 1;
  two.matrix[0][1] = 2;
  two.matrix[0][2] = 3;
  two.matrix[1][0] = 0;
  two.matrix[1][1] = 4;
  two.matrix[1][2] = 2;
  two.matrix[2][0] = 5;
  two.matrix[2][1] = 2;
  two.matrix[2][2] = 1;

  three.matrix[0][0] = 1;
  three.matrix[0][1] = 4;
  three.matrix[1][0] = 2;
  three.matrix[1][1] = 5;
  three.matrix[2][0] = 3;
  three.matrix[2][1] = 6;

  four.matrix[0][0] = 1;
  four.matrix[0][1] = -1;
  four.matrix[0][2] = 1;
  four.matrix[1][0] = 2;
  four.matrix[1][1] = 3;
  four.matrix[1][2] = 4;

  five.matrix[0][0] = 2;
  five.matrix[0][1] = 5;
  five.matrix[0][2] = 7;
  five.matrix[1][0] = 6;
  five.matrix[1][1] = 3;
  five.matrix[1][2] = 4;
  five.matrix[2][0] = 5;
  five.matrix[2][1] = -2;
  five.matrix[2][2] = -3;

  printf("Первая матрица:\n");
  for (int i = 0; i < 3; i++) {  // Вывод для теста
    for (int j = 0; j < 3; j++) {
      printf("%lf ", one.matrix[i][j]);
      if (j == 3 - 1) printf("\n");
    }
  }
  printf("\n");
  printf("Вторая матрица:\n");
  for (int i = 0; i < 3; i++) {  // Вывод для теста
    for (int j = 0; j < 3; j++) {
      printf("%lf ", two.matrix[i][j]);
      if (j == 3 - 1) printf("\n");
    }
  }
  printf("\n");
  printf("Третья матрица:\n");
  for (int i = 0; i < 3; i++) {  // Вывод для теста
    for (int j = 0; j < 2; j++) {
      printf("%lf ", three.matrix[i][j]);
      if (j == 2 - 1) printf("\n");
    }
  }
  printf("\n");
  printf("Четвёртая матрица:\n");
  for (int i = 0; i < 2; i++) {  // Вывод для теста
    for (int j = 0; j < 3; j++) {
      printf("%lf ", four.matrix[i][j]);
      if (j == 3 - 1) printf("\n");
    }
  }
  printf("\n");
  printf("Пятая матрица:\n");
  for (int i = 0; i < 3; i++) {  // Вывод для теста
    for (int j = 0; j < 3; j++) {
      printf("%lf ", five.matrix[i][j]);
      if (j == 3 - 1) printf("\n");
    }
  }
  printf("\n");
  printf("Шестая матрица:\n");
  for (int i = 0; i < 4; i++) {  // Вывод для теста
    for (int j = 0; j < 4; j++) {
      printf("%lf ", six.matrix[i][j]);
      if (j == 4 - 1) printf("\n");
    }
  }

  printf("\n");
  printf("s21_eq_matrix: %d (первая и вторая матрицы)\n",
         s21_eq_matrix(&one, &two));
  printf("\n");
  printf("s21_sum_matrix: %d (первая и вторая матрицы)\n",
         s21_sum_matrix(&one, &two, &result1));
  for (int i = 0; i < result1.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result1.columns; j++) {
      printf("%lf ", result1.matrix[i][j]);
      if (j == result1.columns - 1) printf("\n");
    }
  }
  printf("\n");
  printf("s21_sub_matrix: %d (первая и вторая матрицы)\n",
         s21_sub_matrix(&one, &two, &result2));
  for (int i = 0; i < result2.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result2.columns; j++) {
      printf("%lf ", result2.matrix[i][j]);
      if (j == result2.columns - 1) printf("\n");
    }
  }
  printf("\n");
  printf("s21_mult_number: %d (первая матрица и 2)\n",
         s21_mult_number(&one, 2, &result3));
  for (int i = 0; i < result3.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result3.columns; j++) {
      printf("%lf ", result3.matrix[i][j]);
      if (j == result3.columns - 1) printf("\n");
    }
  }
  printf("\n");
  printf("s21_mult_matrix: %d (третья и четвёртая матрицы)\n",
         s21_mult_matrix(&three, &four, &result4));
  for (int i = 0; i < result4.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result4.columns; j++) {
      printf("%lf ", result4.matrix[i][j]);
      if (j == result4.columns - 1) printf("\n");
    }
  }
  printf("\n");
  printf("s21_transpose: %d (третья матрица)\n",
         s21_transpose(&three, &result5));
  for (int i = 0; i < result5.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result5.columns; j++) {
      printf("%lf ", result5.matrix[i][j]);
      if (j == result5.columns - 1) printf("\n");
    }
  }
  printf("\n");
  printf("s21_calc_complements: %d (вторая матрица)\n",
         s21_calc_complements(&two, &result6));
  for (int i = 0; i < result6.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result6.columns; j++) {
      printf("%lf ", result6.matrix[i][j]);
      if (j == result6.columns - 1) printf("\n");
    }
  }
  printf("\n");
  double m = 0;
  printf("s21_determinant: %d (шестая матрица)\n", s21_determinant(&six, &m));
  printf("determinant =  %lf (шестая матрица)\n", m);
  printf("\n");

  printf("s21_inverse_matrix: %d (пятая матрица)\n",
         s21_inverse_matrix(&five, &result7));
  for (int i = 0; i < result7.rows; i++) {  // Вывод для теста
    for (int j = 0; j < result7.columns; j++) {
      printf("%lf ", result7.matrix[i][j]);
      if (j == result7.columns - 1) printf("\n");
    }
  }
  s21_remove_matrix(&one);
  s21_remove_matrix(&two);
  s21_remove_matrix(&three);
  s21_remove_matrix(&four);
  s21_remove_matrix(&five);
  s21_remove_matrix(&six);
  return 0;
}