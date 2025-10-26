CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
TESTFLAGS = -lgtest -lgtest_main -pthread -g3
LIB=$(wildcard *.cpp)

all: clean s21_matrix_oop.a

s21_matrix_oop.a: 
	$(CC) -c $(LIB)
	ar rcs s21_matrix_oop.a *.o 
	ranlib s21_matrix_oop.a
	rm -rf *.o

test:
	$(CC) $(CFLAGS) ./tests/*.cpp -o s21_matrix_test $(TESTFLAGS) -L. -l:s21_matrix_oop.a
	./s21_matrix_test

clang_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h *.cpp tests/*.cpp *.h 

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes ./s21_matrix_test

clean: 
	rm -f *.o *.a s21_matrix_test

rebuild: clean all

