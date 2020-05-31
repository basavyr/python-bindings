#include "array-create.hh"

template <typename T>
T math_function(const T &element)
{
    return std::forward<T>(element * element + 1);
}

template <typename T>
std::vector<T> generate_array(size_t arrsize, const T &init)
{
    std::vector<T> retarray;
    for (size_t id = 0; id < arrsize; ++id)
    {
        retarray.emplace_back(math_function<T>(init + id));
    }
    return retarray;
}

PyObject *return_array(PyObject *self, PyObject *args)
{
    Py_ssize_t size;
    int init; //declare without pointer for easier access to memory
    if (!PyArg_ParseTuple(args, "ni", &size, &init))
        return NULL;
    PyObject *v = PyList_New(size);
    //python 2 requires item set in order to avoid SEG_FAULT
    auto Cxx_array = generate_array<long>(size, init);
    for (int id = 0; id < size; id++)
    {
        // auto current_C_number = math_function<long>(id);
        PyObject *number = PyLong_FromLong(Cxx_array.at(id));
        // PyObject *number = PyInt_FromLong(id + 1);
        PyList_SetItem(v, id, number);
    }
    PyObject *result;
    result = Py_BuildValue("O", v);
    Py_DECREF(v);
    return result;
}

PyObject *select_array(PyObject *self, PyObject *args)
{
    Py_ssize_t size;
    int init;
    Py_ssize_t left_id, right_id;
    if (!PyArg_ParseTuple(args, "ninn", &size, &init, &left_id, &right_id))
        return NULL;
    Py_ssize_t arr_dim = right_id - left_id;
    PyObject *py_array = PyList_New(arr_dim);
    auto cxx_array = generate_array<long>(size, init);
    Py_ssize_t local_id = 0;
    for (auto id = left_id; id < right_id; ++id)
    {
        PyObject *element = PyLong_FromLong(cxx_array.at(id));
        PyList_SetItem(py_array, local_id, element);
        local_id = local_id + 1;
    }
    PyObject *result;
    result = Py_BuildValue("O", py_array);
    Py_DECREF(py_array);
    cxx_array.clear();
    return result;
}