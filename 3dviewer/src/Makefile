DESTDIR = ./bin/

.PHONY: all install uninstall clean dvi html

all:
	mkdir -p build
	cmake . -B build
	$(MAKE) -C build
install: all
	mkdir -p $(DESTDIR)
	cp build/3D_Viewer $(DESTDIR)
uninstall:
	rm -f $(DESTDIR)/3D_Viewer
test: all
	cd build && ctest --output-on-failure
clean:
	rm -rf build
dvi:
	makeinfo --dvi manual.texi
html:
	makeinfo --html manualRU.texi
dist:
	tar -cf 3D_Viewer.tar back controller front lib	Makefile
linter:
	clang-format -style=Google -i `find . -type f \( -iname "*.cc" -o -iname "*.cpp" -o -iname "*.tpp" -o -iname "*.h" \)`