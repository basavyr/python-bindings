#include "Python.h"

#include <vector>
#include <cmath>
#include <chrono>
#include <string>
#include <functional>
#include <iostream>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

static PyObject *return_array(PyObject *self, PyObject *args);
static const char return_array_MethodName[] = "return_array";
static const char return_array_MethodDoc[] = "This function returns an array of fixed length";

static PyObject *select_array(PyObject *self, PyObject *args);
static const char select_array_MethodName[] = "select_array";
static const char select_array_MethodDoc[] = "This function returns a sliced array, between a predefined interval";

static const char moduleDoc_py2[] = "Documentation for the module - py2 version";
static const char moduleDoc_py3[] = "Documentation for the module - py3 version";
static const char moduleName[] = "retarray";

static PyMethodDef return_arrayMethodDef[] = {
    {return_array_MethodName, return_array, METH_VARARGS, return_array_MethodDoc},
    {select_array_MethodName, select_array, METH_VARARGS, select_array_MethodDoc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
static struct PyModuleDef return_arrayModuleDef
{
    PyModuleDef_HEAD_INIT,
        moduleName,
        moduleDoc_py3,
        -1,
        return_arrayMethodDef
};
PyMODINIT_FUNC PyInit_retarray(void)
{
    Py_Initialize();
    PyObject *m;
    m = PyModule_Create(&return_arrayModuleDef);
    return m;
}
#else
PyMODINIT_FUNC initretarray(void)
{
    Py_InitModule3(moduleName, return_arrayMethodDef, moduleDoc_py2);
}
#endif