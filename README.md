# libirmin

[irmin](https://github.com/mirage/irmin) C library using [ocaml-ctypes](https://github.com/ocamllabs/ocaml-ctypes) inverted stubs.

See [irmin.h](https://github.com/zshipko/libirmin/blob/main/irmin.h) for available functions and types.

## C bindings

NOTE: All strings returned from `libirmin` should be released using `free`, but `Irmin*` types should be released using the
corresponding `irmin_*_free` function.

## Python bindings

Python bindings can be installed using:

```
$ python3 -m pip install . --user
```

Or, to install directly from this repository:

```
$ python3 -m pip install git+https://github.com/zshipko/libirmin.git
```


