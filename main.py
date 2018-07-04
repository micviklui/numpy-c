import numpy as np
import numpyc

a = numpyc.return_ndarray()
print(numpyc.return_ndarray.__doc__,
      type(a),
      a.shape,
      a)

x = np.array([1, 2, 3])
y = numpyc.inout_ndarray(x)
print(numpyc.inout_ndarray.__doc__,
      type(y),
      y.shape,
      y)

import pyc
class D(object):
    def __init__(self, _x):
        self.x = _x

din = D(x)
dout = pyc.inout_pyobj(din)
print(x, din, dout)
