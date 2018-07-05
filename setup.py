import os
#import sysconfig
import numpy as np
from setuptools import setup
from setuptools import Extension


ext_pyc = Extension(
    'pyc',
    sources=[
        'pyc.c',
    ],
    include_dirs=[
        #sysconfig.get_config_vars()['INCLUDEDIR'],
        # probably use output of (see also pkgconfig)
        #   pkg-config --libs glib-2.0
        #   pkg-config --cflags glib-2.0
        '/usr/include/glib-2.0',
        '/usr/lib/x86_64-linux-gnu/glib-2.0/include',
        os.path.abspath('./')
    ],
    libraries=[
        'glib-2.0',
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
