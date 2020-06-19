#include "Python.h"
#include "structmember.h"

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

static const char null_string_object[] = "<0_py_string>";

//Class objects (variables)
typedef struct
{
    PyObject_HEAD
        PyObject *py_list;
    PyObject *py_norm;
    PyObject *py_which;
    PyObject *py_with;
    PyObject *py_string;
} MClass;

//Destructor object
static void MClass_dealloc(MClass *self)
{
    Py_XDECREF(self->py_list);
    Py_XDECREF(self->py_norm);
    Py_XDECREF(self->py_which);
    Py_XDECREF(self->py_with);
    Py_XDECREF(self->py_string);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *MClass_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    MClass *self;

    self = (MClass *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        //Alternative
        //  self->py_list = Py_BuildValue("");
        // self->py_list = PyUnicode_FromString("<0_py_list>");
        self->py_list = PyList_New(0);
        if (self->py_list == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        // self->py_norm = PyUnicode_FromString("<0_py_norm>");
        self->py_norm = PyLong_FromLong(-1);
        if (self->py_norm == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        // self->py_which = PyUnicode_FromString("<0_py_which>");
        self->py_which = PyLong_FromLong(-1);
        if (self->py_which == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        // self->py_with = PyUnicode_FromString("<0_py_with>");
        self->py_with = PyLong_FromLong(-1);
        if (self->py_with == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }

        // self->py_string = PyBytes_FromString(null_string_object);
        self->py_string = PyBytes_FromString("");
        if (self->py_string == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
    }
    return (PyObject *)self;
}

static int MClass_init(MClass *self, PyObject *args, PyObject *kwds)
{
    //Class variables
    PyObject *py_list = nullptr;
    PyObject *py_norm = nullptr;
    PyObject *py_which = nullptr;
    PyObject *py_with = nullptr;
    PyObject *py_string = nullptr;

    //tmp object to store the parsed arguments
    PyObject *tmp;

    static char *kwlist[] = {"list", "norm", "which", "with", "string", NULL};

    //* there is the String Type which can be used for storing the string into the C-object py_string (not working in Py3>)
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O!O!O!O!O!", kwlist, &PyList_Type, &py_list, &PyLong_Type, &py_norm, &PyLong_Type, &py_which, &PyLong_Type, &py_with, &PyBytes_Type, &py_string))
        return NULL;

    if (py_list)
    {
        tmp = self->py_list;
        Py_INCREF(py_list);
        self->py_list = py_list;
        Py_XDECREF(tmp);
    }

    if (py_norm)
    {
        tmp = self->py_norm;
        Py_INCREF(py_norm);
        self->py_norm = py_norm;
        Py_XDECREF(tmp);
    }

    if (py_which)
    {
        tmp = self->py_which;
        Py_INCREF(py_which);
        self->py_which = py_which;
        Py_XDECREF(tmp);
    }

    if (py_with)
    {
        tmp = self->py_with;
        Py_INCREF(py_with);
        self->py_with = py_with;
        Py_XDECREF(tmp);
    }

    if (py_string)
    {
        tmp = self->py_string;
        Py_INCREF(py_string);
        self->py_string = py_string;
        Py_XDECREF(tmp);
    }

    return 0;
}

static PyMemberDef MClass_MemberDef[] = {
    {"py_list", T_OBJECT_EX, offsetof(MClass, py_list), 0, "A python list"},
    {"py_norm", T_OBJECT_EX, offsetof(MClass, py_norm), 0, "The norm of the array"},
    {"py_which", T_OBJECT_EX, offsetof(MClass, py_which), 0, "The element from the array to be replaced"},
    {"py_with", T_OBJECT_EX, offsetof(MClass, py_with), 0, "The element which will replace the required number"},
    {"py_string", T_OBJECT_EX, offsetof(MClass, py_string), 0, "A string for creating a list"},
    {NULL} /* Sentinel */
};

PyObject *MClass_stringer(MClass *self, PyObject *args);
PyObject *MClass_content(MClass *self);
PyObject *MClass_normalize(MClass *self, PyObject *args);
PyObject *MClass_sort(MClass *self, PyObject *args);

static PyMethodDef MClass_MethodDef[] = {
    {"sort", (PyCFunction)MClass_sort, METH_VARARGS, "Returns the string from the class py_string byte object"},
    {"normalize", (PyCFunction)MClass_normalize, METH_VARARGS, "Returns the string from the class py_string byte object"},
    {"stringer", (PyCFunction)MClass_stringer, METH_VARARGS, "Returns the string from the class py_string byte object"},
    {"name", (PyCFunction)MClass_content, METH_NOARGS, "Returns the variables from the class object"},
    {NULL} /* Sentinel */
};

static PyTypeObject MClassType = {
    PyVarObject_HEAD_INIT(NULL, 0) "mclass.MClass", /* tp_name */
    sizeof(MClass),                                 /* tp_basicsize */
    0,                                              /* tp_itemsize */
    (destructor)MClass_dealloc,                     /* tp_dealloc */
    0,                                              /* tp_print */
    0,                                              /* tp_getattr */
    0,                                              /* tp_setattr */
    0,                                              /* tp_reserved */
    0,                                              /* tp_repr */
    0,                                              /* tp_as_number */
    0,                                              /* tp_as_sequence */
    0,                                              /* tp_as_mapping */
    0,                                              /* tp_hash  */
    0,                                              /* tp_call */
    0,                                              /* tp_str */
    0,                                              /* tp_getattro */
    0,                                              /* tp_setattro */
    0,                                              /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
        Py_TPFLAGS_BASETYPE, /* tp_flags */
    "MClass objects",        /* tp_doc */
    0,                       /* tp_traverse */
    0,                       /* tp_clear */
    0,                       /* tp_richcompare */
    0,                       /* tp_weaklistoffset */
    0,                       /* tp_iter */
    0,                       /* tp_iternext */
    MClass_MethodDef,        /* tp_methods */
    MClass_MemberDef,        /* tp_members */
    0,                       /* tp_getset */
    0,                       /* tp_base */
    0,                       /* tp_dict */
    0,                       /* tp_descr_get */
    0,                       /* tp_descr_set */
    0,                       /* tp_dictoffset */
    (initproc)MClass_init,   /* tp_init */
    0,                       /* tp_alloc */
    MClass_new,              /* tp_new */
};

static struct PyModuleDef MClass_ModuleDef = {
    PyModuleDef_HEAD_INIT,
    "mclass",
    "mclass module containing MClass Multi-Class extension",
    -1,
    MClass_MethodDef,
};

PyMODINIT_FUNC PyInit_mclass(void)
{
    Py_Initialize();
    PyObject *m = PyModule_Create(&MClass_ModuleDef);

    if (PyType_Ready(&MClassType) < 0)
        return NULL;

    Py_INCREF(&MClassType);
    PyModule_AddObject(m, "MClass", (PyObject *)&MClassType);

    return m;
}
