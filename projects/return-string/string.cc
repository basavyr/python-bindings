#include "return_string.h"
#include <string>
#include <iostream>

// std::string return_string(char *p)
// {
//     std::string result_string = "Hi ";
//     result_string.append(std::string(p));
//     result_string.append("!\n");
//     return result_string;
// }

// static PyObject *showstring(PyObject *self, PyObject *args)
// {
//     PyObject *result = NULL;
//     char *string;
//     if (!PyArg_ParseTuple(args, "s", &string))
//         return NULL;
//     result = Py_BuildValue("s", return_string(string).c_str()); //transform the string to a c-string
//     return result;
// }

int main()
{
    char *string = "Darwin";
    std::cout << return_string(string).c_str();
}