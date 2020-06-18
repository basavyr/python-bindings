#include "class-module.hh"

PyObject *MClass_content(MClass *self)
{
    if (self->py_list == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "py_list");
        return NULL;
    }

    if (self->py_norm == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "py_norm");
        return NULL;
    }

    if (self->py_which == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "py_which");
        return NULL;
    }

    if (self->py_with == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "py_with");
        return NULL;
    }

    if (self->py_string == NULL)
    {
        PyErr_SetString(PyExc_AttributeError, "py_string");
        return NULL;
    }

    //show how many objects are not initialized
    int count_nulls = 0;
    if (PyList_GET_SIZE(self->py_list) == 0)
        count_nulls++;
    if (self->py_norm == PyLong_FromLong(-1))
        count_nulls++;
    if (self->py_which == PyLong_FromLong(-1))
        count_nulls++;
    if (self->py_with == PyLong_FromLong(-1))
        count_nulls++;
    // if (self->py_string == PyBytes_FromString(null_string_object))
    if (self->py_string == PyBytes_FromString(""))
        count_nulls++;

    PyObject *result;
    result = Py_BuildValue("OOOOOi", self->py_list, self->py_norm, self->py_which, self->py_with, self->py_string, count_nulls);
    return result;
}

PyObject *MClass_stringer(MClass *self, PyObject *args)
{
    // if (self->py_string == NULL)
    // {
    //     PyErr_SetString(PyExc_AttributeError, "py_string");
    //     return NULL;
    // }

    // if (!PyBytes_Check(self->py_string))
    //     return self->py_string;

    PyObject *temp = nullptr;
    if (!PyArg_ParseTuple(args, "|O!", &PyBytes_Type, &temp))
        return NULL;

    if (temp == NULL)
        return PyUnicode_FromString("<0_bytes>");

    auto my_string = PyBytes_AsString(temp);
    PyObject *result;
    result = Py_BuildValue("s", my_string);
    return result;
}

PyObject *MClass_normalize(MClass *self, PyObject *args)
{

    PyObject *local_norm = nullptr;
    PyObject *compute_norm;
    if (!PyArg_ParseTuple(args, "|O!", &PyLong_Type, &local_norm))
        return NULL;

    if (local_norm)
        compute_norm = local_norm;
    else
    {
        compute_norm = self->py_norm;
        // local_norm = self->py_norm;
    }

    if (PyList_Check(self->py_list) && PyLong_Check(self->py_norm))
    {
        Py_ssize_t py_list_size = PyList_GET_SIZE(self->py_list);

        for (auto id = 0; id < py_list_size; ++id)
        {
            PyObject *current_element = PyList_GetItem(self->py_list, id);

            if (!PyLong_Check(current_element))
            {
                PyErr_SetString(PyExc_AttributeError, "The list must contain only long-format items");
                return NULL;
            }

            auto current_normed_element = std::round(PyLong_AsLong(current_element) / PyLong_AsLong(compute_norm));

            PyList_SetItem(self->py_list, id, PyLong_FromLong(current_normed_element));
        }

        PyObject *result;
        result = Py_BuildValue("OOO", self->py_list, self->py_norm, compute_norm);

        return result;
    }

    // if (!PyList_Check(self->py_list))
    // {
    //     PyErr_SetString(PyExc_AttributeError, "The intialized py_list is not valid!");
    //     return NULL;
    // }
    // PyObject *temp_norm = nullptr;

    // if (!PyArg_ParseTuple(args, "|O!", &PyLong_Type, &temp_norm))
    //     return NULL;

    // if (temp_norm == NULL)
    //     temp_norm = self->py_norm;
    PyErr_SetString(PyExc_AttributeError, "The intialized py_list is not valid!");
    return NULL;
}

PyObject *MClass_sort(MClass *self)
{
    Py_ssize_t py_list_size = PyList_GET_SIZE(self->py_list);
    if (!py_list_size || !PyList_Check(self->py_list))
    {
        PyErr_SetString(PyExc_AttributeError, "This is an empty array - no sorting can be performed");
        return NULL;
    }
    std::vector<long> cxx_list;
    for (auto id = 0; id < py_list_size; ++id)
    {
        PyObject *current_py_list_item = PyList_GetItem(self->py_list, id);
        if (!PyLong_Check(current_py_list_item))
        {
            PyErr_SetString(PyExc_AttributeError, "The array contains non-float elements");
            return NULL;
        }
        cxx_list.emplace_back(PyLong_AsLong(current_py_list_item));
    }
    std::sort(cxx_list.begin(), cxx_list.end());
    PyObject *sorted_py_list = PyList_New(py_list_size);
    for (auto id = 0; id < py_list_size; ++id)
    {
        PyObject *current_sorted_element = PyLong_FromLong(cxx_list.at(id));
        PyList_SetItem(sorted_py_list, id, current_sorted_element);
    }
    PyObject *result;
    result = Py_BuildValue("O", sorted_py_list);
    return result;
}