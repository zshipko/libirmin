PREFIX?=/usr/local

SOEXT?=so

.PHONY: build
build:
	@rm -rf py/irmin/libirmin.$(SOEXT) py/irmin/irmin.h
	@mkdir -p include
	@mkdir -p lib
	dune build
	cp _build/default/irmin.h  ./include
	cp _build/default/libirmin.$(SOEXT) ./lib
	cp _build/default/irmin.h  py/irmin
	cp _build/default/libirmin.$(SOEXT) py/irmin

clean:
	@dune clean
	@rm -rf lib py/irmin/libirmin.$(SOEXT) py/irmin/irmin.h
	@cd rust && cargo clean

install:
	install ./include/irmin.h $(PREFIX)/include
	install ./lib/libirmin.$(SOEXT) $(PREFIX)/lib

uninstall:
	rm -f $(PREFIX)/include/irmin.h
	rm -f $(PREFIX)/lib/libirmin.$(SOEXT)

test-rust: build
	cargo test -- --test-threads=1

.PHONY: test
test: build
	$(CC) -o test/test test/test.c -I . -L . -lirmin -g
	LD_LIBRARY_PATH=. DYLD_FALLBACK_LIBRARY_PATH=. ./test/test
