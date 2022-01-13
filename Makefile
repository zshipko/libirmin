PREFIX?=$(HOME)/.local

SOEXT?=so

build:
	dune build

clean:
	dune clean

install:
	@mkdir -p $(PREFIX)/include $(PREFIX)/lib
	install ./include/irmin.h $(PREFIX)/include/irmin.h
	install ./lib/libirmin.$(SOEXT) $(PREFIX)/lib/libirmin.$(SOEXT)

uninstall:
	rm -f $(PREFIX)/include/irmin.h
	rm -f $(PREFIX)/lib/libirmin.$(SOEXT)
	@rmdir $(PREFIX)/lib 2> /dev/null || :
	@rmdir $(PREFIX)/include 2> /dev/null || :

.PHONY: test
test: build
	dune runtest
