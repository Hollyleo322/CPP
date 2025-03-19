cppflags=g++ -Wall -Wextra -Werror -std=c++17 -o
.PHONY: test s21_matrix_oop.a
all : s21_matrix_oop.a gcov_report
s21_matrix_oop.a:
	g++ -c s21_matrix.cpp -o s21_matrix.o
	ar rcs s21_matrix_oop.a s21_matrix.o
	rm -rf *.o
clean:
	rm -rf *.info *.gcda *.gcno test_gcov *.info report test
test:
	$(cppflags) test test.cpp ./s21_matrix_oop.a -lgtest
	./test
gcov_report:
	$(cppflags) test_gcov --coverage test.cpp s21_matrix.cpp -lgtest
	./test_gcov
	lcov -t "name" -o s21_matrixplus.info -c -d .
	genhtml -o report s21_matrixplus.info
style:
	clang-format -style=google -n *.cpp *.h
format:
	clang-format -style=google -i *.cpp *.h
go:
	$(cppflags) go main.cpp ./s21_matrix_oop.a
	./go