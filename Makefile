PREFIX?=$(HOME)/.local

SOEXT?=so

.PHONY: build
build:
	@rm -rf py/irmin/libirmin.$(SOEXT) py/irmin/irmin.h
	@mkdir -p include
	@mkdir -p lib
	@dune build
	@cp _build/default/irmin.h  ./include
	@cp _build/default/libirmin.$(SOEXT) ./lib
	@cp _build/default/irmin.h  py/irmin
	@cp _build/default/libirmin.$(SOEXT) py/irmin


clean:
	@dune clean
	@rm -rf lib py/irmin/libirmin.$(SOEXT) py/irmin/irmin.h
	@cd rust && cargo clean

install:
	@mkdir -p $(PREFIX)/include $(PREFIX)/lib
	install ./include/irmin.h $(PREFIX)/include/irmin.h
	install ./lib/libirmin.$(SOEXT) $(PREFIX)/lib/libirmin.$(SOEXT)

uninstall:
	rm -f $(PREFIX)/include/irmin.h
	rm -f $(PREFIX)/lib/libirmin.$(SOEXT)
	@rmdir $(PREFIX)/lib 2> /dev/null || :
	@rmdir $(PREFIX)/include 2> /dev/null || :

test-rust: build
	cargo test -- --test-threads=1

test-python: build
	py.test py/test.py

.PHONY: test
test: build
	$(CC) -o test/test test/test.c -I . -L lib -lirmin -g
	LD_LIBRARY_PATH=lib DYLD_FALLBACK_LIBRARY_PATH=lib ./test/test

test-all: test test-rust test-python
