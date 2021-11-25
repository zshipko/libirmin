# libirmin

[irmin](https://github.com/mirage/irmin) C library using [ocaml-ctypes](https://github.com/ocamllabs/ocaml-ctypes) inverted stubs.

See [irmin.h](https://github.com/zshipko/libirmin/blob/main/include/irmin.h) for available functions and types.

## C bindings

NOTE: All strings returned from `libirmin` should be released using `free`, but `Irmin*` types should be released using the
corresponding `irmin_*_free` function.

## Rust bindings

Rust bindings exist in the `rust` directory, to use them in your project add the following to your `Cargo.toml` file:

```
irmin = {git = "https://github.com/zshipko/libirmin"}
```

NOTE: `libirmin.so` should be available somewhere in your `LD_LIBRARY_PATH` to ensure it's linked correctly

## Python bindings

Python bindings can be installed using:

```
$ python3 -m pip install . --user
```

Or, to install directly from this repository:

```
$ python3 -m pip install git+https://github.com/zshipko/libirmin.git
```


