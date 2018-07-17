import sys
import ctypes
import numpy as np


if sys.platform == 'linux':
    libname = 'test_ctypes.so'
elif sys.platform == 'darwin':
    libname = 'test_ctypes.cpython-37m-darwin.so'
libdir = './'
lib = np.ctypeslib.load_library(libname, libdir)

py_add_one = lib.add_one
py_add_one.argtypes = [ctypes.c_int]

py_print_list = lib.print_list

py_show_array = lib.show_array
py_show_array.argtypes = [
    np.ctypeslib.ndpointer(float, flags='aligned, contiguous'),
    np.ctypeslib.c_intp,
]

py_get_array = lib.get_array
py_get_array.argtypes = [
    np.ctypeslib.c_intp,
]
py_get_array.restype = np.ctypeslib.ndpointer(float, flags='aligned, contiguous')


value = 5
results = py_add_one(value)
print(results)
py_print_list()

a = np.arange(5) * 99.
py_show_array(a , len(a))
print(a)

x = py_get_array(25);
print(x)

