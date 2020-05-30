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

std::string join_strings(const std::string &s1, const std::string &s2)
{
    return std::forward<std::string>("The program joined: " + s1 + ' ' + s2 + '\n');
}

PyObject *showdate(PyObject *self, PyObject *args)
{
    char *user = NULL;
    PyObject *result = NULL;

    if (!PyArg_ParseTuple(args, "s", &user))
        return NULL;

    auto time = return_date(std::chrono::system_clock::now());
    auto retval = hey(time, user);
    result = Py_BuildValue("s", retval.c_str());
    // Py_DECREF(result);
    return result;
}

PyObject *join(PyObject *self, PyObject *args)
{
    char *string1 = NULL;
    char *string2 = NULL;
    PyObject *result = NULL;

    //parse the arguments
    if (!PyArg_ParseTuple(args, "ss", &string1, &string2))
        return NULL;

    auto retval = join_strings(std::string(string1), std::string(string2));

    result = Py_BuildValue("s", retval.c_str());
    // Py_DECREF(result); //? produces SEG_FAULT when built with Python3
    return result;
}