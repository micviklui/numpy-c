#include <Python.h>
#include <numpy/arrayobject.h>
#include <glib.h>
#include <stdio.h>


static PyObject *inout_pyobj(PyObject *self, PyObject *args);
static PyObject *out_pylist(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
    {"inout_pyobj", inout_pyobj, METH_VARARGS, "input and return a python object"},
    {"out_pylist", out_pylist, METH_VARARGS, "output a python list object"},
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

static PyObject *out_pylist(PyObject *self, PyObject *args) {
    GArray *a = g_array_new(FALSE, FALSE, sizeof(char*));
    char* first = "hello", *second = "there", *third = "world";
    g_array_append_val(a, first);
    g_array_append_val(a, second);
    g_array_append_val(a, third);
    printf("There are now %d items in the array\n", a->len);
    printf("The first item is '%s'\n", g_array_index(a, char*, 0));
    printf("The third item is '%s'\n", g_array_index(a, char*, 2));
    g_array_remove_index(a, 1);
    printf("There are now %d items in the array\n", a->len);

    PyListObject *list = (PyListObject *)Py_BuildValue("[]");
    for (int i = 0; i < a->len; i++) {
        PyObject *e = Py_BuildValue("s", g_array_index(a, char*, i));
        PyList_Append(list, e);
    }
    for (int i = 0; i < a->len; i++) {
        PyObject *e = Py_BuildValue("i", i);
        PyList_Append(list, e);
    }
    g_array_free(a, FALSE);

    //Py_INCREF(Py_None);
    //return Py_None;
    return list;
}
