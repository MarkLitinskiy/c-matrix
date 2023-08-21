# s21_matrix
Реализация собственной версии библиотеки для работы с матрицами s21_matrix.a.  
Project date: 01-2023

## Project Build

Сборка проекта осуществляется командой `make` в папке `src`, существуют следующие цели:  
- `s21_math.a` - сборка самой библиотеки,  
- `test` - запуск тестирования,  
- `gcov_report` - просмотр покрытия тестов (необходима утилита lcov),  
- `valgrind` - проверка на утечки утилитой valgrind,  
- `leaks` - проверка на утечки утилитой leaks на Mac OS,  
- `rebuild` - пересобрать проект,  
- `check_style` - проверка на соответствие clang формату,  
- `docker_check` - тестирование и проверка на утечки через docker в системе ubuntu,  
- `clean` - очистить проект от временных файлов.

## Структура матрицы на языке C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Операции над матрицами

Все операции (кроме сравнения матриц) возвращают результирующий код:  
- 0 - OK
- 1 - Ошибка, некорректная матрица   
- 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой нельзя провести вычисления и т.д.)

## Функции для работы с матрицами
- Создание матриц (create_matrix)  
```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

- Очистка матриц (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

- Сравнение матриц (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

- Сложение (sum_matrix) и вычитание матриц (sub_matrix)

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

- Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

- Транспонирование матрицы (transpose)

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

- Минор матрицы и матрица алгебраических дополнений (calc_complements)

```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

- Определитель матрицы (determinant)

```c
int s21_determinant(matrix_t *A, double *result);
```

- Обратная матрица (inverse_matrix)

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

## Описание

- Библиотека разработана на языке Си стандарта C11 с использованием компилятора gcc 
- Решение оформлено как статическая библиотека (с заголовочным файлом s21_matrix.h)
- Библиотека разработана в соответствии с принципами структурного программирования
- Подготовлено полное покрытие unit-тестами функций библиотеки c помощью библиотеки Check
- Unit-тесты покрывают не менее 80% каждой функции
- Предусмотрен Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix.a, gcov_report)
- В цели gcov_report формируется отчёт gcov в виде html страницы. 
- Проверяемая точность дробной части - максимум 6 знаков после запятой.
