cppflags=g++ -Wall -Wextra -Werror --std=c++17 -g -o
.PHONY: test set_test vector_test stack_test map_test multiset_test array_test
test: set_test vector_test stack_test map_test multiset_test list_test queue_test array_test

all: gcov_report 

set_test:
	$(cppflags) set_test tests/test_set.cpp -lgtest
	./set_test
vector_test:
	$(cppflags) vector_test tests/test_vector.cpp -lgtest
	./vector_test
stack_test:
	$(cppflags) stack_test tests/test_stack.cpp -lgtest
	./stack_test
map_test:
	$(cppflags) map_test tests/test_map.cpp -lgtest
	./map_test
multiset_test:
	$(cppflags) multiset_test tests/test_multiset.cpp -lgtest
	./multiset_test
list_test:
	$(cppflags) list_test tests/test_list.cpp -lgtest
	./list_test
queue_test:
	$(cppflags) queue_test tests/test_queue.cpp -lgtest
	./queue_test
array_test:
	$(cppflags) array_test tests/test_array.cpp -lgtest
	./array_test

gcov_report:
	$(cppflags) set_test_gcov --coverage tests/test_set.cpp -lgtest
	./set_test_gcov
	$(cppflags) vector_test_gcov --coverage tests/test_vector.cpp -lgtest
	./vector_test_gcov
	$(cppflags) stack_test_gcov --coverage tests/test_stack.cpp -lgtest
	./stack_test_gcov
	$(cppflags) map_test_gcov --coverage tests/test_map.cpp -lgtest
	./map_test_gcov
	$(cppflags) multiset_test_gcov --coverage tests/test_multiset.cpp -lgtest
	./multiset_test_gcov
	$(cppflags) list_test_gcov --coverage tests/test_list.cpp -lgtest
	./list_test_gcov
	$(cppflags) queue_test_gcov --coverage tests/test_queue.cpp -lgtest
	./queue_test_gcov
	$(cppflags) array_test_gcov --coverage tests/test_array.cpp -lgtest
	./array_test_gcov
	lcov -t "name" -o s21_containers.info -c -d . --exclude "/usr/include/*" --exclude "./templates/BinaryTree.*" --exclude "./tests/*"
	genhtml -o report s21_containers.info

clean:
	rm -rf *.gcno *.gcda *_gcov report *_test *.info *VALGRIND.txt

style:
	clang-format --style=google -n templates/*.h templates/*.tpp tests/*.cpp

format:
	clang-format --style=google -i templates/*.h templates/*.tpp tests/*.cpp

mem_check: test
ifeq ($(OS), Darwin)
	leaks --atExit -- list_test
	leaks --atExit -- multiset_test
	leaks --atExit -- set_test
	leaks --atExit -- vector_test
	leaks --atExit -- map_test
	leaks --atExit -- queue_test
	leaks --atExit -- stack_test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=list_test_VALGRIND.txt ./list_test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=multiset_test_VALGRIND.txt ./multiset_test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=set_test_VALGRIND.txt ./set_test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=vector_test_VALGRIND.txt ./vector_test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=map_test_VALGRIND.txt ./map_test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=queue_test_VALGRIND.txt ./queue_test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=stack_test_VALGRIND.txt ./stack_test
endif