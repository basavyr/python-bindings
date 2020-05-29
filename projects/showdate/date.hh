#include "Python.h"
#include "structmember.h"

#include <chrono>
#include <string>
#include <iostream>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

//module function is defined the .cc file
static PyObject *date(PyObject *self, PyObject *args);

//registration table
static PyMethodDef showdateModule_methods[] = {
    {"showdate", date, METH_VARARGS, "Doc: A function that returns the input string"},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
static struct PyModuleDef showdateModuleDef = {
    PyModuleDef_HEAD_INIT,
    "showdate",
    "Doc: A function that returns the input string",
    -1,
    showdateModule_methods};

PyMODINIT_FUNC PyInit_showdate(void)
{
    return PyModule_Create(&showdateModuleDef);
}
#else
// module initializer for python2
PyMODINIT_FUNC initshowdate(void)
{
    Py_InitModule3("showdate", showdateModule_methods, "moduleDocs");
}
#endif