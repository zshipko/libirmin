PREFIX?=/usr/local

ifeq ($(shell uname -s),Darwin)
	SOEXT=dylib
else
	SOEXT?=so
endif


build:
	mkdir -p out
	dune build
	cp _build/default/lib/irmin.h ./out
	cp _build/default/lib/libirmin.$(SOEXT) ./out

clean:
	dune clean
	rm -rf out

install:
	install out/irmin.h $(PREFIX)/include
	install out/libirmin.$(SOEXT) $(PREFIX)/lib

uninstall:
	rm -f $(PREFIX)/include/irmin.h
	rm -f $(PREFIX)/lib/libirmin.$(SOEXT)

