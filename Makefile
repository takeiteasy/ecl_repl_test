BUILDDIR=build

default: turtle

builddir: $(BUILDIR)
	mkdir -p $(BUILDDIR)

ecl:
	cd deps/ecl; \
	./configure \
		    --with-tcp \
		    --with-clos-streams \
		    --with-asdf \
		    --with-defsystem \
		    --with-fpe; \
	make; \
	mv build/* ../../$(BUILDDIR); \
	cp -r src/h ../../$(BUILDDIR); \
	rm -rf build

turtle:
	clang src/main.c -I$(BUILDDIR) -rpath $(BUILDDIR) -L$(BUILDDIR) -lecl -o $(BUILDDIR)/turtle

all: builddir ecl turtle
