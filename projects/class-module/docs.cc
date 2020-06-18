//! HEADER
#include <Python.h>
#include <structmember.h>

typedef struct
{
    PyObject_HEAD // no semicolon
        PyObject *name;
    int number;
} BindingsBasavyr;

static void BindingsBasavyr_dealloc(BindingsBasavyr *self)
{
    Py_XDECREF(self->name);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *BindingsBasavyr_new(PyTypeObject *type, PyObject *args,
                                     PyObject *kwds)
{
    BindingsBasavyr *self;

    self = (BindingsBasavyr *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->name = Py_BuildValue("");
        if (self->name == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
        self->number = 0;
    }

    return (PyObject *)self;
}

static int BindingsBasavyr_init(BindingsBasavyr *self, PyObject *args)
{
    int n;
    PyObject *nameobj = NULL;
    PyObject *tmp;
    if (!PyArg_ParseTuple(args, "Oi", &nameobj, &n))
        return NULL;

    if (nameobj)
    {
        tmp = self->name;
        Py_INCREF(nameobj);
        self->name = nameobj;
        Py_XDECREF(tmp);
    }

    self->number = n;
    return 0;
}

static PyMemberDef BindingsBasavyr_members[] = {
    {"name", T_OBJECT_EX, offsetof(BindingsBasavyr, name), 0, "BindingsBasavyr name"},
    {"number", T_INT, offsetof(BindingsBasavyr, number), 0, "BindingsBasavyr number"},
    {NULL} /* Sentinel */
};

static PyObject *miami(BindingsBasavyr *self);
static PyObject *newyork(BindingsBasavyr *self);
static PyObject *islist(BindingsBasavyr *self);
static PyObject *getsecondelement(BindingsBasavyr *self);

static PyMethodDef BindingsBasavyr_methods[] = {
    {"miami", (PyCFunction)miami, METH_NOARGS, "Divides number by 2"},
    {"nyc", (PyCFunction)newyork, METH_NOARGS, "Doubles number"},
    {"islist", (PyCFunction)islist, METH_NOARGS, "checks if the name object is a list or not"},
    {"getsecondelement", (PyCFunction)getsecondelement, METH_NOARGS, "getsecondelement of the name "},
    {NULL} /* Sentinel */
};

static PyTypeObject BindingsBasavyrType = {
    PyVarObject_HEAD_INIT(NULL, 0) "bindingsbasavyr.BindingsBasavyr", /* tp_name */
    sizeof(BindingsBasavyr),                                          /* tp_basicsize */
    0,                                                                /* tp_itemsize */
    (destructor)BindingsBasavyr_dealloc,                              /* tp_dealloc */
    0,                                                                /* tp_print */
    0,                                                                /* tp_getattr */
    0,                                                                /* tp_setattr */
    0,                                                                /* tp_reserved */
    0,                                                                /* tp_repr */
    0,                                                                /* tp_as_number */
    0,                                                                /* tp_as_sequence */
    0,                                                                /* tp_as_mapping */
    0,                                                                /* tp_hash  */
    0,                                                                /* tp_call */
    0,                                                                /* tp_str */
    0,                                                                /* tp_getattro */
    0,                                                                /* tp_setattro */
    0,                                                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                         /* tp_flags */
    "BindingsBasavyr objects",                                        /* tp_doc */
    0,                                                                /* tp_traverse */
    0,                                                                /* tp_clear */
    0,                                                                /* tp_richcompare */
    0,                                                                /* tp_weaklistoffset */
    0,                                                                /* tp_iter */
    0,                                                                /* tp_iternext */
    BindingsBasavyr_methods,                                          /* tp_methods */
    BindingsBasavyr_members,                                          /* tp_members */
    0,                                                                /* tp_getset */
    0,                                                                /* tp_base */
    0,                                                                /* tp_dict */
    0,                                                                /* tp_descr_get */
    0,                                                                /* tp_descr_set */
    0,                                                                /* tp_dictoffset */
    (initproc)BindingsBasavyr_init,                                   /* tp_init */
    0,                                                                /* tp_alloc */
    BindingsBasavyr_new,                                              /* tp_new */
};

static struct PyModuleDef bindingsbasavyr = {
    PyModuleDef_HEAD_INIT,
    "bindingsbasavyr",
    "bindingsbasavyr module containing BindingsBasavyr class",
    -1,
    BindingsBasavyr_methods,
};

PyMODINIT_FUNC PyInit_bindingsbasavyr(void)
{
    Py_Initialize();
    PyObject *m = PyModule_Create(&bindingsbasavyr);

    if (PyType_Ready(&BindingsBasavyrType) < 0)
        return NULL;

    Py_INCREF(&BindingsBasavyrType);
    PyModule_AddObject(m, "BindingsBasavyr", (PyObject *)&BindingsBasavyrType);

    return m;
}


//? SOURCE

#include "bindings.hh"

static PyObject *miami(BindingsBasavyr *self)
{
    if (self->number > 1)
        self->number /= 2;

    return PyLong_FromLong((long)self->number);
}

static PyObject *newyork(BindingsBasavyr *self)
{
    if (self->number < 100)
        self->number *= 2;

    return PyLong_FromLong((long)self->number);
}

static PyObject *islist(BindingsBasavyr *self)
{
    bool condition = false;
    if (PyList_Check(self->name))
        condition = true;
    PyObject *result = NULL;
    char *islist = "IT IS OK";
    char *isnotlist = "IT IS NOT OK";
    if (condition)
        result = Py_BuildValue("s", islist);
    else
    {
        result = Py_BuildValue("s", isnotlist);
    }
    return result;
}

static PyObject *getsecondelement(BindingsBasavyr *self)
{
    PyObject *result = NULL;
    if (PyList_Check(self->name))
    {
        Py_ssize_t listsize = PyList_Size(self->name) - 1;
        PyObject *data = PyList_New(listsize);
        for (Py_ssize_t i = 0; i < listsize; ++i)
        {
            PyObject *value = PyList_GetItem(self->name, i);
            PyList_SetItem(data, i, value);
            // Py_XDECREF(value);
        }
        result = data;
        // Py_XDECREF(data);
    }
    return result;
}
