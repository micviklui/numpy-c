#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>


static PyObject *inout_pyobj(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"inout_pyobj", inout_pyobj, METH_VARARGS, "input and return a python object"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initpyc(void) {

    PyObject *m = Py_InitModule3("pyc", module_methods, "test python object - c handling");
    if (m == NULL)
        return;

    /* Load `numpy` functionality. */
    import_array();
}

static PyObject *inout_pyobj(PyObject *self ,PyObject *args) {
    PyObject *o;
    if (!PyArg_ParseTuple(args, "O", &o))
        return NULL;

    PyObject *xattr = Py_BuildValue("s", "x");
    PyObject *ox = PyObject_GetAttr(o, xattr);
    PyObject *x_array = PyArray_FROM_OTF(ox, NPY_DOUBLE, NPY_IN_ARRAY);
    if (x_array == NULL ) {
        Py_XDECREF(x_array);
        return NULL;
    }

    int xlen = (int)PyArray_DIM(x_array, 0);
    double *x = (double*)PyArray_DATA(x_array);
    Py_XDECREF(x_array);

    for (int i = 0; i < xlen; i++) {
        printf("%d: %f\n", i, x[i]);
    }

    return o;
}


