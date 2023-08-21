CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g -pedantic
LDFLAGS=-g
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
LIBSOURCES=s21*.c
LIBOBJECTS=s21*.o
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lpthread -lcheck -pthread -lrt -lm -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: s21_matrix.a 

s21_matrix.a: $(LIBOBJECTS)
	$(CC) $(CFLAGS) -c $(LIBSOURCES)
	ar -crs s21_matrix.a $(LIBOBJECTS)
	rm -f *.o

test: s21_matrix.a
	$(CC) $(CFLAGS) mineTests.c s21_matrix.c -o run.out $(CHECKFLAGS) -lgcov --coverage
	./run.out

gcov_report: s21_matrix.a
	$(CC) $(CFLAGS) $(PROFILE_FLAGS) s21_matrix.c mineTests.c -o gcov_test $(CHECKFLAGS)
	./gcov_test
	lcov -t "test" -o report.info -c -d . 
	genhtml -o gcov_report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index.html

rebuild: clean all

check_style:
	cp ../materials/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

docker_check:
	docker build -t "valgrind:1.0" .
	docker run --rm -v $PWD:/tmp -w /tmp valgrind:1.0

valgrind: test
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./run.out
	 make clean

leaks: test
	CK_FORK=no leaks --atExit -- ./run.out
	make clean

clean:
	rm -rf *.o \
		*.a \
		*.so \
		*.gcno \
		*gcda \
		*.gcov \
		gcov_report.* \
		*.dSYM \
        RESULT_VALGRIND.txt \
		*.out \
        unit-test \
        vtests_run \
		run \
		gcov \
		report/ \
		gcov_report/ \
		report.info \
		gcov_report \
		gcov_test \
