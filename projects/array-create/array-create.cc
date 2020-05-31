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
        retarray.emplace_back(math_function<T>(init+id));
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