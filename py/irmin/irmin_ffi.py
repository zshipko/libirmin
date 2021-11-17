import cffi  # type: ignore

ffi = cffi.FFI()
with open("../out/irmin.h") as h_file:
    lines = h_file.readlines()
    lines = [
        line for line in lines if not '#include' in line
        and not '#define' in line and not 'static' in line
    ]
    lines.append("void free(void*);")
    ffi.cdef('\n'.join(lines))

ffi.set_source(
    "_irmin_ffi",
    # Since you're calling a fully-built library directly, no custom source
    # is necessary. You need to include the .h files, though, because behind
    # the scenes cffi generates a .c file that contains a Python-friendly
    # wrapper around each of the functions.
    '#include "../out/irmin.h"',
    # The important thing is to include the pre-built lib in the list of
    # libraries you're linking against:
    libraries=["irmin"],
    library_dirs=['../out'],
    include_dirs=['../out'],
    extra_link_args=["-Wl,-rpath,."],
)

ffi.compile()