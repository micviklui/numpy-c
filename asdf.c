/*
 * adapted from https://stackoverflow.com/a/27831120/1469176
 *
 */

#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>


static PyObject *fill_array(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"fill_array", fill_array, METH_VARARGS, "fill the input array"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initasdf(void) {

    PyObject *m = Py_InitModule3("asdf", module_methods, "test numpy-c array handling");
    if (m == NULL)
        return;

    /* Load `numpy` functionality. */
    import_array();
}

static PyObject *fill_array(PyObject *self ,PyObject *args) {

    double *vector = calloc(2, sizeof(double));
    vector[0] = -12.345;
    vector[1] = 1000.0;

    int nd = 1;
    npy_intp *dims = calloc(nd , sizeof(npy_intp));
    dims[0] = 2;

    PyObject *ret  = PyArray_SimpleNewFromData(nd, dims, (int)NPY_DOUBLE, vector);
    return ret;
}
