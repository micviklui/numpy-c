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

#https://stackoverflow.com/questions/4355524/getting-data-from-ctypes-array-into-numpy
#https://docs.python.org/3/library/ctypes.html#passing-pointers-or-passing-parameters-by-reference
py_get_array = lib.get_array
py_get_array.argtypes = [
    np.ctypeslib.ndpointer(float, flags='aligned, contiguous'),
    np.ctypeslib.c_intp,
    #np.ctypeslib.ndpointer(float, flags='aligned, contiguous'),
    #np.ctypeslib.c_intp,
    ctypes.POINTER(ctypes.c_double),
    ctypes.c_int,
]

value = 5
results = py_add_one(value)
print(results)
py_print_list()

a = np.arange(5) * 99.
py_show_array(a , len(a))
print(a)

print('get_array')
#out = ctypes.POINTER(ctypes.c_double)()
#out = ctypes.pointer(ctypes.c_double())
out = ctypes.c_double()
n_out = ctypes.c_int()

py_get_array(a, len(a), ctypes.byref(out), n_out)
print(out)
print(np.ctypeslib.as_array(out))
a_buffer = np.core.multiarray.int_asbuffer(
    ctypes.addressof(out), 8*n_out)
print(np.frombuffer(a_buffer, float))

