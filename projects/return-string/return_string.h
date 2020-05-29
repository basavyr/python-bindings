#include "Python.h"
#include "structmember.h"

#include <string>
#include <iostream>

// #if PY_MAJOR_VERSION >= 3
// #define PY3K
// #endif

//module function is defined the .cc file

std::string return_string(char *p)
{
    std::string result_string = "Hi ";
    result_string.append(std::string(p));
    result_string.append("!\n");
    return result_string;
}

static PyObject *showstring(PyObject *self, PyObject *args)
{
    PyObject *result = NULL;
    char *string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    result = Py_BuildValue("s", return_string(string).c_str()); //transform the string to a c-string
    return result;
}

//registration table
static PyMethodDef showstringModule_methods[] = {
    {"showstring", showstring, METH_VARARGS, "Doc: A function that returns the input string"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef showstringModuleDef = {
    PyModuleDef_HEAD_INIT,
    "showstring",
    "Doc: A function that returns the input string",
    -1,
    showstringModule_methods};

PyMODINIT_FUNC PyInit_showstring(void)
{
    return PyModule_Create(&showstringModuleDef);
}