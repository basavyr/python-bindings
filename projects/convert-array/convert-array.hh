#include "Python.h"

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

constexpr char ModuleName[] = "convarray";
constexpr char ModuleDoc[] = "This module converts a Python list object into a C/C++ vector";

PyObject *getarray(PyObject *self, PyObject *args);
constexpr char getarrayMethodName[] = "array";
constexpr char getarrayMethodDoc[] = "This method takes a Python object and converts it into a C Python List object";

PyObject *getsize(PyObject *self, PyObject *args);
constexpr char getsizeMethodName[] = "size";
constexpr char getsizeMethodDoc[] = "Get the size of the array";

PyObject *countlist(PyObject *self, PyObject *args);
constexpr char countlistMethodName[] = "count";
constexpr char countlistMethodDoc[] = "Get the count frequency for a certain element of the list";

PyObject *sorter(PyObject *self, PyObject *args);
constexpr char sorterMethodName[] = "sorter";
constexpr char sorterMethodDoc[] = "Sort the python list";

PyObject *norm(PyObject *self, PyObject *args);
constexpr char normMethodName[] = "norm";
constexpr char normMethodDoc[] = "Normalize the vector to the input argument";

PyObject *slice(PyObject *self, PyObject *args);
constexpr char sliceMethodName[] = "slice";
constexpr char sliceMethodDoc[] = "Cut the vector to predefined intervals";

PyObject *replace(PyObject *self, PyObject *args);
constexpr char replaceMethodName[] = "replace";
constexpr char replaceMethodDoc[] = "Replace any number that equals the input argument with another predefined argument";

static PyMethodDef convarrayMethodDef[] = {
    {getarrayMethodName, getarray, METH_VARARGS, getarrayMethodDoc},
    {getsizeMethodName, getsize, METH_VARARGS, getsizeMethodDoc},
    {countlistMethodName, countlist, METH_VARARGS, countlistMethodDoc},
    {sorterMethodName, sorter, METH_VARARGS, sorterMethodDoc},
    {sliceMethodName, slice, METH_VARARGS, sliceMethodDoc},
    {normMethodName, norm, METH_VARARGS, normMethodDoc},
    {replaceMethodName, replace, METH_VARARGS, replaceMethodDoc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K

static struct PyModuleDef convarrayModuleDef = {
    PyModuleDef_HEAD_INIT,
    ModuleName,
    ModuleDoc,
    -1,
    convarrayMethodDef};
//init function
PyMODINIT_FUNC PyInit_convarray(void)
{
    Py_Initialize();
    PyObject *m;
    m = PyModule_Create(&convarrayModuleDef);
    return m;
}
#else
PyMODINIT_FUNC initconvarray(void)
{
    Py_InitModule3(ModuleName, convarrayMethodDef, ModuleDoc);
}
#endif