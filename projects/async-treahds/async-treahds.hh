#include "Python.h"

#include <vector>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <future>

#if PY_MAJOR_VERSION >= 3
#define PY3K
#endif

static PyObject *task_generator(PyObject *self, PyObject *args);
static const char task_generatorMethodName[] = "maketasks";
static const char task_generatorMethodDoc[] = "a method for generating tasks and then run them asynchronously";

static PyObject *thread_runner(PyObject *self, PyObject *args);
static const char thread_runnerMethodName[] = "threadrunner";
static const char thread_runnerMethodDoc[] = "this is a method that runs operations in a thread, and it is timed out";

static const char moduleDoc[] = "This is an extension for working with threads asynchronously";
static const char moduleName[] = "asyncxx";

static PyMethodDef asyncxxMethodDef[] = {
    {thread_runnerMethodName, thread_runner, METH_VARARGS, thread_runnerMethodDoc},
    {task_generatorMethodName, task_generator, METH_VARARGS, task_generatorMethodDoc},
    {NULL, NULL, 0, NULL}};

#ifdef PY3K
static struct PyModuleDef asyncxxModuleDef = {
    PyModuleDef_HEAD_INIT,
    moduleName,
    moduleDoc,
    -1,
    asyncxxMethodDef};
PyMODINIT_FUNC PyInit_asyncxx(void)
{
    Py_Initialize();
    PyObject *m;
    m = PyModule_Create(&asyncxxModuleDef);
    return m;
}
#else
PyMODINIT_FUNC initasyncxx(void)
{
    Py_InitModule3(moduleName, asyncxxMethodDef, moduleDoc);
}
#endif