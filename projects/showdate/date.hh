#include "Python.h"
// #include "structmember.h"

#include <chrono>
#include <string>
#include <iostream>
#include <functional>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

static PyObject *showdate(PyObject *self, PyObject *args);
static const char showdate_methodName[] = "showdate";
static const char showdate_methodDoc[] = "This function takes an input string and shows it together with the current date and time.";

static PyObject *join(PyObject *self, PyObject *args);
static const char join_methodName[] = "join";
static const char join_methodDoc[] = "This function takes two input strings and joins them together";

static const char moduleDoc_py2[] = "This is the documentation for the module - Python2 build"; //documentation for python2 extension build
static const char moduleDoc_py3[] = "This is the documentation for the module - Python3 build"; //documentation for python3 extension build
static const char moduleName[] = "showdate";                                                    //name of the module (same for both python versions)

//registration table
static PyMethodDef showdateMethodDef[] = {
    {showdate_methodName, showdate, METH_VARARGS, showdate_methodDoc},
    {join_methodName, join, METH_VARARGS, join_methodDoc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
//creating the module for the python3 build process
static struct PyModuleDef showdateModuleDef = {
    PyModuleDef_HEAD_INIT,
    moduleName,
    moduleDoc_py3,
    -1,
    showdateMethodDef}; //import the created methods into the py3 module
//the init function for building with python3
PyMODINIT_FUNC PyInit_showdate(void) //the init function when building with python3
{
    Py_Initialize();
    PyObject *m;
    m = PyModule_Create(&showdateModuleDef);
    return m;
}
#else
// module initializer for python2
PyMODINIT_FUNC initshowdate(void) //! ----> on Darwin the init function must be init<modulename> without any _ symbol between them
{
    Py_InitModule3(moduleName, showdateMethodDef, moduleDoc_py2);
    //the init function for building wth python2
}
#endif