import cffi  # type: ignore
import os

self_path = os.path.dirname(__file__)
libirmin_prefix = os.getenv("LIBIRMIN_PREFIX")

if libirmin_prefix is not None:
    loc = os.path.join(libirmin_prefix, "lib")
    header_loc = os.path.join(libirmin_prefix, "include")
elif os.path.exists(os.path.join(self_path, "libirmin.so")):
    # In repo
    loc = self_path
    header_loc = self_path
else:
    prefix = os.getenv("OPAM_SWITCH_PREFIX")
    local = os.path.expanduser("~/.local")
    if prefix is not None and os.path.exists(
            os.path.join(prefix, "lib", "libirmin", "libirmin.so")):
        loc = os.path.join(prefix, "lib", "libirmin", "lib")
        header_loc = os.path.join(prefix, "lib", "libirmin", "include")
    elif prefix is not None and os.path.exists(
            os.path.join(prefix, "lib", "libirmin.so")):
        loc = os.path.join(prefix, "lib")
        header_loc = os.path.join(prefix, "include")
    elif os.path.exists(os.path.join(local, "lib", "libirmin.so")):
        loc = os.path.join(local, "lib")
        header_loc = os.path.join(local, "include")
    else:
        loc = "/usr/local/lib"
        header_loc = "/usr/local/include"

ffi = cffi.FFI()
with open(os.path.join(header_loc, "irmin.h")) as h_file:
    lines = h_file.readlines()
    lines = [
        line for line in lines if '#include' not in line
        and '#define' not in line and 'static' not in line
    ]
    lines.append("void free(void*);")
    ffi.cdef('\n'.join(lines))

lib = ffi.dlopen(os.path.join(loc, "libirmin.so"))
