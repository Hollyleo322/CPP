cppflags=g++ -Wall -Wextra -Werror --std=c++17 -o
cflags=gcc -Wall -Wextra -Werror -std=c11 -o
.PHONY: test snake_desktop s21_snake.a s21_tetris.a
install: snake_desktop snake_cli tetris_desktop tetris_cli
uninstall: clean
s21_snake.a:
	g++ -c brick_game/snake/snake.cpp -o brick_game/snake/s21_snake.o -Dsnake
	ar rcs gui/desktop/s21_snake/s21_snake.a brick_game/snake/s21_snake.o
	rm -rf brick_game/snake/*.o
s21_tetris.a:
	gcc -c brick_game/tetris/s21_tetris.c -o brick_game/tetris/s21_tetris.o
	ar rcs gui/desktop/s21_snake/s21_tetris.a brick_game/tetris/s21_tetris.o
	rm -rf brick_game/tetris/*.o
tetris_desktop: s21_tetris.a 
	cmake gui/desktop/s21_snake -B tetris_desktop -Dsnake=OFF
	$(MAKE) -C tetris_desktop
tetris_cli: s21_tetris.a
	mkdir tetris_cli
	gcc -c gui/cli/gui.c -o gui/cli/gui.o
	g++ -c gui/cli/main_cli.cpp -o gui/cli/main_cli.o
	g++ -o game gui/cli/gui.o gui/cli/main_cli.o -lncurses ./gui/desktop/s21_snake/s21_tetris.a -g
	mv game tetris_cli
snake_desktop: s21_snake.a
	cmake gui/desktop/s21_snake -B snake_desktop
	$(MAKE) -C snake_desktop
snake_cli: s21_snake.a
	mkdir snake_cli
	gcc -c gui/cli/gui.c -o gui/cli/gui.o -Dsnake
	g++ -c gui/cli/main_cli.cpp -o gui/cli/main_cli.o -Dsnake
	g++ -o game gui/cli/gui.o gui/cli/main_cli.o ./gui/desktop/s21_snake/s21_snake.a -lncurses -Dsnake -g
	mv game snake_cli
clean:
	rm -rf snake_desktop gui/desktop/s21_snake/*.a tetris_desktop gui/cli/*.o *.o tetris_cli brick_game/snake/*.o *.o snake_cli *.gcda *.gcno *.info test_gcov report test s21_snake
test: s21_snake.a
	$(cppflags) test test.cpp ./gui/desktop/s21_snake/s21_snake.a -lgtest
	./test
gcov_report:
	$(cppflags) test_gcov --coverage test.cpp brick_game/snake/snake.cpp -lgtest
	./test_gcov
	lcov -t "name" -o s21_snake.info -c -d . --exclude "/usr/include/*" --ignore mismatch
	genhtml -o report s21_snake.info 
style:
	clang-format -n --style=google *.cpp brick_game/snake/*.cpp brick_game/tetris/*.c gui/cli/*.c gui/cli/*.cpp gui/desktop/s21_snake/*.cpp
format:
	clang-format -i --style=google *.cpp brick_game/snake/*.cpp brick_game/tetris/*.c gui/cli/*.c gui/cli/*.cpp gui/desktop/s21_snake/*.cpp
dist:
	tar -cf brick_game2.tar brick_game gui Makefile
dvi:
	makeinfo --dvi manual.texi
html:
	makeinfo --html manual.texi
