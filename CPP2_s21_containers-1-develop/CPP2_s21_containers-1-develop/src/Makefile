CC = g++
FLAGS = -std=c++17 -Wall -Werror -Wextra

ifeq ($(shell uname), Darwin)
	TESTFLAGS = -lgtest -lcheck -pthread
	LEAKS = leaks -atExit --
else
	TESTFLAGS = -lgtest -lcheck -lm -lsubunit -pthread
	LEAKS = CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
endif

all: test

test: clean
	$(CC) $(FLAGS) -o tests/s21_containers.test --coverage tests/test.cpp $(TESTFLAGS)
	tests/s21_containers.test

valgrind: clean
	$(CC) $(FLAGS) -o tests/s21_containers.test tests/test.cpp $(TESTFLAGS)
	$(LEAKS) ./tests/s21_containers.test
	cat valgrind.log

clean:
	rm -rf tests/*.gcno tests/*.gcda tests/coverage_html tests/*.test tests/*.info valgrind.log *.gcda *.gcno 
	rm -rf .clang-format =


# Получаем версию lcov
LCOV_VERSION = $(shell lcov --version | grep -oP 'lcov\s+\K\d+\.\d+')

# Устанавливаем флаги в зависимости от версии
ifeq ($(shell test $(LCOV_VERSION) >= 1.15; echo $$?), 0)
  LCOV_FLAGS = --ignore-errors mismatch --ignore-errors inconsistent
else
  LCOV_FLAGS = 
endif


gcov_report: clean test
	lcov -d . -c -o tests/s21_containers.test.info $(LCOV_FLAGS)
	lcov -r tests/s21_containers.test.info "/usr*" -o tests/s21_containers.test.info
	lcov -r tests/s21_containers.test.info "*test*" -o tests/s21_containers.test.info
	genhtml -o tests/coverage_html tests/s21_containers.test.info

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n */*.cpp
	clang-format -n */*.h
	rm -f .clang-format

clang-replace:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i */*.cpp
	clang-format -i */*.h
	rm -f .clang-format
