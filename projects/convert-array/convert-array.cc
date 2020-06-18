#include "convert-array.hh"

PyObject *getarray(PyObject *self, PyObject *args)
{
    PyObject *py_list;
    PyObject *py_element = nullptr;

    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &py_list))
        return NULL;

    Py_ssize_t py_list_size = PyList_GET_SIZE(py_list);

    std::vector<long> cxx_list;
    for (auto id = 0; id < py_list_size; ++id)
    {
        py_element = PyList_GetItem(py_list, id);
        auto cxx_element = PyLong_AsLong(py_element);
        if (cxx_element == -1 && PyErr_Occurred())
        {
            exit(1);
        }
        cxx_list.emplace_back(cxx_element);
    }
    auto okMsg = "The CXX array was generated successfully from the python (list) object";
    if (cxx_list.size() != py_list_size)
        okMsg = "The CXX array failed generating from the python (list) object";
    PyObject *result;
    result = Py_BuildValue("sn", okMsg, py_list_size);

    return result;
}

PyObject *getsize(PyObject *self, PyObject *args)
{
    PyListObject *py_list;
    if (!PyArg_ParseTuple(args, "O", &py_list))
        NULL;
    bool ok = false;
    if (PyList_Check(py_list))
        ok = true;
    PyObject *result;
    auto py_list_size = PyList_GET_SIZE(py_list);
    // const auto nokMsg = "This object is not a list!!!";
    // const auto okMsg = "This object is a valid list!";
    // if (ok)
    // {
    //     result = Py_BuildValue("n", okMsg, size);
    // }
    // else
    // {
    //     result = Py_BuildValue("sn", nokMsg, size);
    // }
    result = Py_BuildValue("n", py_list_size);
    return result;
}

PyObject *countlist(PyObject *self, PyObject *args)
{
    PyObject *py_list;
    PyObject *py_element = nullptr;
    long which;
    if (!PyArg_ParseTuple(args, "O!l", &PyList_Type, &py_list, &which))
        return NULL;

    Py_ssize_t py_list_size = PyList_GET_SIZE(py_list);
    int count = 0;
    for (auto id = 0; id < py_list_size; ++id)
    {
        py_element = PyList_GetItem(py_list, id);
        auto cxx_element = PyLong_AsLong(py_element);
        if (cxx_element != -1. && PyErr_Occurred())
        {
            exit(1);
        }
        if (cxx_element == which)
            count++;
    }
    PyObject *result;
    if (!count)
    {
        auto err = "The element was NOT found in the array!";
        result = Py_BuildValue("s", err);
    }
    else
    {
        auto ok = "Element was found in array ";
        auto ok2 = " times...";
        result = Py_BuildValue("sis", ok, count, ok2);
    }
    return result;
}

PyObject *sorter(PyObject *self, PyObject *args)
{
    std::vector<long> cxx_array;
    int order;

    PyObject *py_list;
    PyObject *py_element = nullptr;

    if (!PyArg_ParseTuple(args, "O!i", &PyList_Type, &py_list, &order))
        return NULL;

    auto compare = [&](long x, long y) {
        if (order == -1)
            return x > y;
        return x < y;
    };

    Py_ssize_t py_list_size = PyList_GET_SIZE(py_list);
    for (auto id = 0; id < py_list_size; ++id)
    {
        py_element = PyList_GetItem(py_list, id);
        auto cxx_element = PyLong_AsLong(py_element);
        if (cxx_element == -1. && PyErr_Occurred())
        {
            exit(1);
        }
        cxx_array.emplace_back(cxx_element);
    }

    std::sort(cxx_array.begin(), cxx_array.end(), compare);

    PyObject *py_ordered_list = PyList_New(py_list_size);
    for (auto id = 0; id < py_list_size; ++id)
    {
        py_element = PyLong_FromLong(cxx_array.at(id));
        PyList_SetItem(py_ordered_list, id, py_element);
    }
    PyObject *result;
    result = Py_BuildValue("O", py_ordered_list);
    return result;
}

PyObject *norm(PyObject *self, PyObject *args)
{
    PyObject *py_list;
    PyObject *py_list_element = nullptr;
    int norm;
    if (!PyArg_ParseTuple(args, "O!i", &PyList_Type, &py_list, &norm))
        return NULL;
    Py_ssize_t py_list_size = PyList_GET_SIZE(py_list);
    for (auto id = 0; id < py_list_size; ++id)
    {
        py_list_element = PyList_GetItem(py_list, id);
        auto cxx_element = PyLong_AsLong(py_list_element);
        if (cxx_element == -1 && PyErr_Occurred())
        {
            exit(1);
        }
        // auto normed_element = std::round(PyLong_AsLong(py_list_element) / norm);
        cxx_element = std::round(cxx_element / norm);
        PyList_SetItem(py_list, id, PyLong_FromLong(cxx_element));
    }
    PyObject *result;
    result = Py_BuildValue("O", py_list);
    return result;
}

PyObject *slice(PyObject *self, PyObject *args)
{
    PyObject *py_list;
    PyObject *py_sliced_list;
    PyObject *py_list_element = nullptr;
    int left, right;
    if (!PyArg_ParseTuple(args, "O!ii", &PyList_Type, &py_list, &left, &right))
        return NULL;
    py_sliced_list = PyList_New(0);
    for (auto id = left; id < right; ++id)
    {
        py_list_element = PyList_GetItem(py_list, id);
        auto cxx_element = PyLong_AsLong(py_list_element);
        if (cxx_element == -1 && PyErr_Occurred())
        {
            exit(1);
        }
        PyList_Append(py_sliced_list, py_list_element);
    }
    PyObject *result;
    result = Py_BuildValue("O", py_sliced_list);
    return result;
}

PyObject *replace(PyObject *self, PyObject *args)
{
    PyObject *py_list;
    PyObject *py_which;
    PyObject *py_with;
    PyObject *current_list_element = nullptr;
    if (!PyArg_ParseTuple(args, "O!O!O!", &PyList_Type, &py_list, &PyLong_Type, &py_which, &PyLong_Type, &py_with))
        return NULL;
    Py_ssize_t py_list_size = PyList_GET_SIZE(py_list);
    for (auto id = 0; id < py_list_size; ++id)
    {
        current_list_element = PyList_GetItem(py_list, id);
        auto x = PyLong_AsLong(py_with);
        if (current_list_element == py_which)
        {
            PyList_SetItem(py_list, id, PyLong_FromLong(x));
        }
    }
    PyObject *result;
    result = Py_BuildValue("O", py_list);
    return result;
}