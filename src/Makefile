.PHONY: all s21_matrix_oop.a
CC = g++
FLAGS = -Wall -Werror -Wextra -g
TEST_FLAGS= -lgtest -lgtest_main
S21_MATRIX_C=s21_*.cpp
S21_MATRIX_O=s21_*.o
COVFLAGS = -fprofile-arcs  -lcheck -ftest-coverage
TESTS=tests

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS+=-lsubunit
endif

all: clean gcov_report

gcov_report: test
	gcov -f *.gcda
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info 
	open report/index.html

test: s21_matrix_oop.a
		$(CC) $(FLAGS) -c test/tests*.cpp
		$(CC) $(FLAGS) --coverage -o test.out tests*.o -lgtest -lgtest_main -L. s21_matrix_oop.a
		./test.out

s21_matrix_oop.a: s21_matrix_oop.o
		ar rc s21_matrix_oop.a s21_matrix_oop.o
		ranlib s21_matrix_oop.a

s21_matrix_oop.o:
		$(CC) $(FLAGS) -c $(COVFLAGS) s21_matrix_oop.cpp


clean:
	rm -rf $(TESTS) *.a *.o *.gcda *.gcno *.gcov *.info *.html report my_test test.out s21_matrix_oop

mem: test
ifeq ($(shell uname -s),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TESTS)
else
	leaks --atExit -- ./$(TESTS)
endif

style:
	clang-format -style=google -i test/*.cpp *.cpp *.h
	clang-format -style=google -n test/*.cpp *.cpp *.h

rebuild: clean all

sample:
	$(CC) $(FLAGS) s21_*.cpp samples.cpp -o my_test -lm
	./my_test
