# s21_matrix
Implementation of our own version of the library for working with matrices s21_matrix.a.  
Project date: 01-2023

## Project Build

The project is built with the `make` command in the `src` folder, there are the following targets:  
- `s21_math.a` - building the library itself,  
- `test` - start testing,  
- `gcov_report` - view test coverage (the lcov utility is required),  
- `valgrind` - check for leaks with valgrind utility,  
- `leaks` - check for leaks with the leaks utility on Mac OS,  
- `rebuild` - rebuild the project,  
- `check_style` - check for clang format compliance,  
- `docker_check` - test and check for leaks via docker on ubuntu system,  
- `clean` - clean the project from temporary files.

## Matrix structure in C:

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

## Operations on matrices

All operations (except matrix comparison) return the resulting code:  
- 0 - OK
- 1 - Error, incorrect matrix   
- 2 - Calculation error (matrix sizes do not match; matrix for which calculations cannot be performed, etc.)

## Functions for working with matrices
- Create matrix (create_matrix)  
```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

- Clearing matrices (remove_matrix)

```c
void s21_remove_matrix(matrix_t *A);
```

- Matrix comparison (eq_matrix)

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

- Addition (sum_matrix) and subtraction of matrices (sub_matrix)

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

- Multiplication of a matrix by a number (mult_number). Multiplication of two matrices (mult_matrix)

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

- Matrix transpose

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

- Minor of matrix and matrix of algebraic complements (calc_complements)

```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

- The determinant of the matrix (determinant)

```c
int s21_determinant(matrix_t *A, double *result);
```

- Inverse matrix (inverse_matrix)

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

## Description

- The library is developed in C11 standard C language using gcc compiler 
- The solution is designed as a static library (with header file s21_matrix.h).
- The library is developed in accordance with the principles of structural programming
- Full coverage of unit-tests of library functions with the help of Check library is prepared.
- Unit-tests should cover at least 80% of each function
- Provide a Makefile for building the library and tests (with targets all, clean, test, s21_matrix.a, gcov_report).
- The gcov_report target should generate a gcov report as an html page. 
- Checked accuracy of the fractional part - maximum 6 decimal places.