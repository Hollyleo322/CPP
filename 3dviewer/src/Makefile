cppflags=g++ -Wall -Wextra -Werror -std=c17 -o

.PHONY:

install:
	mkdir -p build
	cmake . -B build
	$(MAKE) -C build
uninstall:
	rm -rf build
dvi:
	makeinfo --dvi manual.texi
html:
	makeinfo --html manual.texi	