#include "Python.h"
#include "structmember.h"

#include <string>
#include <iostream>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

//module function is defined the .cc file
static PyObject *showstring(PyObject *self, PyObject *args);

//registration table
static PyMethodDef showstringModule_methods[] = {
    {"showstring", showstring, METH_VARARGS, "Doc: A function that returns the input string"},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
static struct PyModuleDef showstringModuleDef = {
    PyModuleDef_HEAD_INIT,
    "showstring",
    "Doc: A function that returns the input string - python3",
    -1,
    showstringModule_methods};
//the init function for building with python3
PyMODINIT_FUNC PyInit_showstring(void)
{
    return PyModule_Create(&showstringModuleDef);
}
#else
// module initializer for python2
PyMODINIT_FUNC initshowstring(void)
{
    Py_InitModule3("showstring", showstringModule_methods, "moduleDocs - python2");
}
#endif