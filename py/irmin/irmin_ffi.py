import cffi  # type: ignore
import os

loc = os.path.dirname(__file__)

ffi = cffi.FFI()
with open(os.path.join(loc, "irmin.h")) as h_file:
    lines = h_file.readlines()
    lines = [
        line for line in lines if '#include' not in line
        and '#define' not in line and 'static' not in line
    ]
    lines.append("void free(void*);")
    ffi.cdef('\n'.join(lines))

lib = ffi.dlopen(os.path.join(loc, "libirmin.so"))
