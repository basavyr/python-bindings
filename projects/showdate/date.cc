#include "date.hh"

std::string return_date(std::chrono::system_clock::time_point tp)
{
    auto now = std::chrono::system_clock::to_time_t(tp);
    std::string s = ctime(&now);
    return s;
}

std::string hey(std::string time, std::string user)
{
    std::string say_hi = "Hey there " + user;
    say_hi.append("\nIt's: ");
    say_hi.append(time);
    return say_hi + '\n';
}

PyObject *date(PyObject *self, PyObject *args)
{
    char *user = NULL;
    PyObject *result = NULL;

    if (!PyArg_ParseTuple(args, "s", &user))
        return NULL;

    auto time = return_date(std::chrono::system_clock::now());
    auto ret_val = hey(time, user);
    result = Py_BuildValue("s", ret_val.c_str());
    // Py_DECREF(result);
    return result;
}