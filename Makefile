PREFIX?=$(HOME)/.local

SOEXT?=so

OCAML_WHERE=`ocamlc -where`/../..

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


opam_install:
	mkdir -p $(OCAML_WHERE)/../lib/libirmin
	install _build/default/irmin.h $(OCAML_WHERE)/lib/libirmin/irmin.h
	install _build/default/libirmin.so $(OCAML_WHERE)/lib/libirmin.so

opam_uninstall:
	rm -rf $(OCAML_WHERE)/lib/libirmin
	rm -f $(OCAML_WHERE)/lib/libirmin.so

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

test-python: build
	py.test py/test.py

.PHONY: test
test: build
	$(CC) -o test/test test/test.c -I . -L lib -lirmin -g
	LD_LIBRARY_PATH=lib DYLD_FALLBACK_LIBRARY_PATH=lib ./test/test

test-all: test test-rust test-python
