# libirmin

[irmin](https://github.com/mirage/irmin) C library using [ocaml-ctypes](https://github.com/ocamllabs/ocaml-ctypes) inverted stubs.

See [irmin.h](https://github.com/zshipko/libirmin/blob/main/include/irmin.h) for available functions and types.


## C bindings

- `IrminX` values should be released using the corresponding `irmin_X_free` function.
- The following types can safely be cast to `IrminValue*`/`IrminContents`:
  - `IrminString`
  - `IrminCommit`
  - `IrminHash`
  - `IrminPath`
  - `IrminTree`
  - `IrminInfo`

### Compiling

To compile `irmin.h` and `libirmin.so`, run:

```
$ make
```

After that completes `irmin.h` can be found in `include/` and `libirmin.so` will be in `lib/`

### Installation

To install/uninstall `irmin.h` and `libirmin.so`:

```
$ opam install .
$ opam uninstall libirmin
```

`irmin.h` and `libirmin.so` will be copied to `$OPAM_SWITCH_PREFIX/lib/libirmin/include` and
`$OPAM_SWITCH_PREFIX/lib/libirmin/lib` - this is where the Rust and Python bindings will check.

### Running tests

Testing is handled by `dune`:

```
$ dune runtest
```

## Usage

See [README_LIBIRMIN](README_LIBIRMIN.md)

## Rust bindings

See [irmin-rs](https://github.com/mirage/irmin-rs)

## Python bindings

See [irmin-py](https://github.com/mirage/irmin-py)
