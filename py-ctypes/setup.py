import os
#import sysconfig
import numpy as np
from setuptools import setup
from setuptools import Extension

extlib = Extension(
    'test_ctypes',
    define_macros=[],
    sources=[
        'test_ctypes.c',
    ],
    depends=[],
    include_dirs=[
        os.path.abspath('./')
    ],
    #libraries=[
    #    'm',
    #],
    #extra_compile_args=[
    #    '-funroll-all-loops'
    #]
)

setup(
    name='test-ctypes',
    version='0.0',
    scripts=[
        'main.py'
    ],
    ext_modules=[
        extlib,
    ],
)
