#include "Python.h"
#include "structmember.h"

#include <string>
#include <iostream>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

//module function is defined the .cc file
static PyObject *string(PyObject *self, PyObject *args);

const char method_doc[] = "This is the documentation for the method";
const char module_doc[] = "This is the documentation for the module";

//registration table
static PyMethodDef showstringModule_methods[] = {
    {"showstring", string, METH_VARARGS, method_doc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
static struct PyModuleDef showstringModuleDef = {
    PyModuleDef_HEAD_INIT,
    "showstring",
    module_doc,
    -1,
    showstringModule_methods};
//the init function for building with python3
PyMODINIT_FUNC PyInit_showstring(void)
{
    Py_Initialize();
    PyObject *m;
    m = PyModule_Create(&showstringModuleDef);
    return m;
}
#else
// module initializer for python2
PyMODINIT_FUNC initshowstring(void)
{
    Py_InitModule3("showstring", showstringModule_methods, module_doc);
}
#endif