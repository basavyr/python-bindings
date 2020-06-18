#include "Python.h"

//CXX headers that are needed for generating random numbers
#include <random>
#include <vector>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

static const char moduleDoc[] = "This is an extension for generating random numbers (integers) using a Mersenne Twister from the C++ standard libraries";
static const char moduleName[] = "twister";

static PyObject *twist(PyObject *self, PyObject *args);
static const char twist_methodName[] = "twist";
static const char twist_methodDoc[] = "This method returns an array of arbitrary length, that contains random integers between a fixed interval";

static PyMethodDef twisterMethodDef[] = {
    {twist_methodName, twist, METH_VARARGS, twist_methodDoc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K

static struct PyModuleDef twisterModuleDef = {
    PyModuleDef_HEAD_INIT,
    moduleName,
    moduleDoc,
    -1,
    twisterMethodDef};
PyMODINIT_FUNC PyInit_twister(void)
{
    Py_Initialize();
    PyObject *m;
    m = PyModule_Create(&twisterModuleDef);
    return m;
}

#else

PyMODINIT_FUNC inittwister(void)
{
    Py_InitModule3(moduleName, twisterMethodDef, moduleDoc);
}

#endif