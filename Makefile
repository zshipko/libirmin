PREFIX?=/usr/local

ifeq ($(shell uname -s),Darwin)
	SOEXT=dylib
else
	SOEXT?=so
endif


build:
	@rm -rf irmin.h libirmin.$(SOEXT)
	dune build
	cp _build/default/lib/irmin.h  .
	cp _build/default/lib/libirmin.$(SOEXT) .

clean:
	@dune clean
	@rm -rf irmin.h libirmin.$(SOEXT)

install:
	install irmin.h $(PREFIX)/include
	install libirmin.$(SOEXT) $(PREFIX)/lib

uninstall:
	rm -f $(PREFIX)/include/irmin.h
	rm -f $(PREFIX)/lib/libirmin.$(SOEXT)

.PHONY: test
test: build
	$(CC) -o test/test test/test.c -I _build/default/lib/ -L _build/default/lib/ -lirmin -g
	LD_LIBRARY_PATH=_build/default/lib ./test/test
