import cffi,pathlib
""" Build the CFFI Python bindings """
print("Building CFFI Module")
ffi = cffi.FFI()
this_dir = pathlib.Path().absolute()

h_file_name = this_dir / "bookshelf_IO.h"
with open(h_file_name) as h_file:
    ffi.cdef(h_file.read())
    
ffi.set_source(
    "bookshelf",
    # Since you're calling a fully-built library directly, no custom source
    # is necessary. You need to include the .h files, though, because behind
    # the scenes cffi generates a .c file that contains a Python-friendly
    # wrapper around each of the functions.
    '#include "bookshelf_IO.h"',
    # The important thing is to include the pre-built lib in the list of
    # libraries you're linking against:
    libraries=["bookshelf"],
    library_dirs=[this_dir.as_posix()],
    extra_link_args=["-Wl,-rpath,."],
)

ffi.compile()