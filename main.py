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
