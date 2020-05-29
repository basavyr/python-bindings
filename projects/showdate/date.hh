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

const char method_doc[] = "This is the documentation for the method";
const char module_doc[] = "This is the documentation for the module";

//registration table
static PyMethodDef showdateModule_methods[] = {
    {"showdate", date, METH_VARARGS, method_doc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
static struct PyModuleDef showdateModuleDef = {
    PyModuleDef_HEAD_INIT,
    "showdate",
    module_doc,
    -1,
    showdateModule_methods};
//the init function for building with python3
PyMODINIT_FUNC PyInit_showdate(void)
{
    return PyModule_Create(&showdateModuleDef);
}
#else
// module initializer for python2
PyMODINIT_FUNC initshowdate(void)
{
    Py_InitModule3("showdate", showdateModule_methods, module_doc);
}
#endif