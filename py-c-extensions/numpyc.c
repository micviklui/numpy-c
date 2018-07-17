/*
 * adapted from https://stackoverflow.com/a/27831120/1469176
 *
 */

#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <stdio.h>


static PyObject *return_ndarray(PyObject *self, PyObject *args);
static PyObject *inout_ndarray(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"return_ndarray", return_ndarray, METH_VARARGS, "return a numpy.ndarray"},
    {"inout_ndarray", inout_ndarray, METH_VARARGS, "input and return a numpy.ndarray"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initnumpyc(void) {

    PyObject *m = Py_InitModule3("numpyc", module_methods, "test numpy-c array handling");
    if (m == NULL)
        return;

    /* Load `numpy` functionality. */
    import_array();
}

static PyObject *return_ndarray(PyObject *self ,PyObject *args) {

    double *vector = calloc(2, sizeof(double));
    vector[0] = -12.345;
    vector[1] = 1000.0;

    int nd = 1;
    npy_intp *dims = calloc(nd , sizeof(npy_intp));
    dims[0] = 2;

    PyObject *ret  = PyArray_SimpleNewFromData(nd, dims, (int)NPY_DOUBLE, vector);
    return ret;
}

static PyObject *inout_ndarray(PyObject *self ,PyObject *args) {

    PyObject *x_obj;

    /* Parse the input tuple */
    if (!PyArg_ParseTuple(args, "O", &x_obj ))
        return NULL;

    /* Interpret the input objects as numpy arrays. */
    PyObject *x_array = PyArray_FROM_OTF(x_obj, NPY_DOUBLE, NPY_IN_ARRAY);

    /* If that didn't work, throw an exception. */
    if (x_array == NULL ) {
        Py_XDECREF(x_array);
        return NULL;
    }

    /* What are the dimensions? */
    int xlen = (int)PyArray_DIM(x_array, 0);

    /* Get pointers to the data as C-types. */
    double *x = (double*)PyArray_DATA(x_array);

    /* Clean up. */
    Py_DECREF(x_array);

    /* Run the algorithm */
    int ylen = xlen + 1;
    double *y = calloc(ylen, sizeof(double));
    for (int i = 0; i < xlen; i++) {
        y[i] = x[i];
    }
    y[ylen-1] = NAN;

    npy_intp dims[1] = {ylen};
    PyObject *ret = PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    memcpy(PyArray_DATA(ret), y, ylen*sizeof(double));
    free(y);

    return ret;
}
