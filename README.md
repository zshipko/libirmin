# libirmin

[irmin](https://github.com/mirage/irmin) C library using [ocaml-ctypes](https://github.com/ocamllabs/ocaml-ctypes) inverted stubs.

See [irmin.h](https://github.com/zshipko/libirmin/blob/main/include/irmin.h) for available functions and types.

## C bindings

- All `Irmin*` values should be released using the corresponding `irmin_*_free` function.
- `IrminString*` can safely be cast to `IrminValue*`

### Compiling

To compile `irmin.h` and `libirmin.so`, run:

```
$ make
```

After that completes `irmin.h` can be found in `include/` and `libirmin.so` will be in `lib/`

### Running tests

```
$ make test          # C tests only
$ make test-rust     # Rust tests only
$ make test-python   # Python tests only
$ make test-all      # Run all tests
```

`py.test` is required to run the python tests: `pip3 install pytest --user`

## Rust bindings

Rust bindings exist in the `rust` directory, to use them in your project add the following to your `Cargo.toml` file:

```
irmin = {git = "https://github.com/zshipko/libirmin"}
```

**Note**: `libirmin.so` should be available somewhere in your `LD_LIBRARY_PATH` to ensure it's linked correctly

## Python bindings

Python bindings exist in the `py` directory and can be installed using:

```
$ python3 -m pip install . --user
```

Or, to install directly from this repository:

```
$ python3 -m pip install git+https://github.com/zshipko/libirmin.git
```


