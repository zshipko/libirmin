PREFIX?=/usr/local

SOEXT?=so

.PHONY: build
build:
	@rm -rf irmin.h libirmin.$(SOEXT) py/irmin/libirmin.$(SOEXT) py/irmin/irmin.h
	dune build
	cp _build/default/lib/irmin.h  .
	cp _build/default/lib/libirmin.$(SOEXT) .
	cp _build/default/lib/irmin.h  py/irmin
	cp _build/default/lib/libirmin.$(SOEXT) py/irmin

clean:
	@dune clean
	@rm -rf libirmin.$(SOEXT) py/irmin/libirmin.$(SOEXT) py/irmin/irmin.h
	@cd rust && cargo clean

install:
	install irmin.h $(PREFIX)/include
	install libirmin.$(SOEXT) $(PREFIX)/lib

uninstall:
	rm -f $(PREFIX)/include/irmin.h
	rm -f $(PREFIX)/lib/libirmin.$(SOEXT)

.PHONY: test
test: build
	$(CC) -o test/test test/test.c -I . -L . -lirmin -g
	LD_LIBRARY_PATH=. DYLD_FALLBACK_LIBRARY_PATH=. ./test/test
