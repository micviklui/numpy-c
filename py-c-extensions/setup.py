import os
import sys
import subprocess

#import sysconfig
import numpy as np
from setuptools import setup
from setuptools import Extension

pkg_glib = subprocess.check_output(
    ["pkg-config", "--cflags", "glib-2.0"]).decode(sys.stdout.encoding)
incl_glib = [p.lstrip('-I') for p in pkg_glib.split()]

ext_pyc = Extension(
    'pyc',
    sources=[
        'pyc.c',
    ],
    include_dirs=[
        np.get_include(),
        #sysconfig.get_config_vars()['INCLUDEDIR'],
        #'/usr/include/glib-2.0',
        #'/usr/lib/x86_64-linux-gnu/glib-2.0/include',
        os.path.abspath('./')
    ] + incl_glib,
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
