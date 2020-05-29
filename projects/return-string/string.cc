#include "string.hh"

std::string return_string(std::string p)
{
    std::string result_string = "Hi ";
    result_string.append(p);
    result_string.append("!\n");
    return result_string;
}

PyObject *showstring(PyObject *self, PyObject *args)
{
    PyObject *result = NULL;
    char *string;
    if (!PyArg_ParseTuple(args, "s", &string))
        return NULL;
    std::string user_copy(string);
    result = Py_BuildValue("s", return_string(user_copy).c_str()); //transform the string to a c-string
    return result;
}
