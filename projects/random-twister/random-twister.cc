#include "random-twister.hh"

//create a seed for debug purposes
static const int seed = 1137;

//creates the twister
static std::random_device rd;
// static std::mt19937 twister{rd()};
static std::mt19937 twister{seed};

int rand_int(int left, int right)
{
    std::uniform_int_distribution<int> int_dist(left, right);
    auto rand_int = int_dist(twister);
    return rand_int;
}

std::vector<int> generate_rand_container(size_t SIZE, int left, int right)
{
    std::vector<int> container;
    for (auto id = 0; id < SIZE; ++id)
    {
        auto current_random_integer = rand_int(left, right);
        container.emplace_back(std::move(current_random_integer));
    }
    return container;
}

double average(const std::vector<int> &v)
{
    double sum = 0.0;
    for (auto &&n : v)
    {
        sum += n;
    }
    return static_cast<double>(sum / v.size());
}

PyObject *twist(PyObject *self, PyObject *args)
{
    Py_ssize_t array_size;
    int left, right;

    if (!PyArg_ParseTuple(args, "nii", &array_size, &left, &right))
        return NULL;

    auto randoms = generate_rand_container(array_size, left, right);
    double avg = average(randoms);

    PyObject *py_randoms = PyList_New(array_size);
    for (int id = 0; id < randoms.size(); ++id)
    {
        PyObject *current_random = PyLong_FromLong(randoms.at(id));
        PyList_SetItem(py_randoms, id, current_random);
    }

    PyObject *result;
    result = Py_BuildValue("Od", py_randoms, avg);
    Py_XDECREF(py_randoms);

    return result;
}