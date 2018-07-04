import os
import numpy as np
from setuptools import setup
from setuptools import Extension


ext_pyc = Extension(
    'pyc',
    sources=[
        'pyc.c',
    ],
    include_dirs=[
        os.path.abspath('./')
    ],
)

ext_numpyc = Extension(
    'numpyc',
    define_macros=[],
    sources=[
        'numpyc.c',
    ],
    depends=[],
    include_dirs=[
        np.get_include(),
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
    name='numpy-c-test',
    version='0.0',
    scripts=[
        'main.py'
    ],
    ext_modules=[
        ext_pyc,
        ext_numpyc,
    ],
)
