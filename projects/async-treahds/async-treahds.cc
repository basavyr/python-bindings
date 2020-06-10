#include "async-treahds.hh"

int do_work(int n_threads, int n_sec, int r_number)
{
    for (int crt_thrd = 0; crt_thrd < n_threads; ++crt_thrd)
    {
        std::this_thread::sleep_for(std::chrono::seconds(n_sec));
        r_number += r_number;
    }
    return r_number;
}

long long measure_work(int n_threads, int n_sec, int r_number)
{
    auto start = std::chrono::system_clock::now();
    auto work_val = do_work(n_threads, n_sec, r_number);
    auto stop = std::chrono::system_clock::now();
    auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    return duration_s;
}

template <typename T>
T worker(int arg, int timer)
{
    bool ok = 0;
    std::this_thread::sleep_for(std::chrono::seconds(timer));
    {
        ok = 1;
    }
    if (ok)
        return arg * 2;
    return 0;
}

template <typename T>
std::vector<std::future<T>> make_tasks(int n_tasks, int task_time)
{
    std::vector<std::future<T>> task_container;
    for (auto task_id = 0; task_id < n_tasks; ++task_id)
    {
        auto new_task = std::async(std::launch::async, worker<T>, task_id, task_time);
        task_container.emplace_back(std::move(new_task));                      //*works
        // task_container.emplace_back(std::forward<T>(new_task)); //*doesnt work
        // task_container.emplace_back(new_task); //!fails
    }
    return task_container;
}

template <typename T>
std::vector<T> unpack_tasks(std::vector<std::future<T>> &futures, int task_time)
{
    std::vector<T> unpacked_tasks;
    for (auto id = 0; id < futures.size(); ++id)
    {
        // auto current_future = futures.at(id).get();
        unpacked_tasks.emplace_back(std::forward<T>(futures.at(id).get())); //the future "Current_future" created in the current scope must be destroyed at the end of the scope, in order to avoid blocking the execution pipeline.
        //since the future is in a type deduction case (template function), the expression binds to a universal reference.
        //one has to forward the task
    }
    return unpacked_tasks;
}

PyObject *thread_runner(PyObject *self, PyObject *args)
{
    int n_threads;
    int n_sec;
    int r_number;
    if (!PyArg_ParseTuple(args, "iii", &n_threads, &n_sec, &r_number))
        return NULL;
    std::string msg_start = "The procees took: \n";
    std::string msg_end = "seconds";
    PyObject *duration = PyLong_FromLongLong(measure_work(n_threads, n_sec, r_number));
    PyObject *result;
    result = Py_BuildValue("sOs", msg_start.c_str(), duration, msg_end.c_str());
    Py_DECREF(duration);
    return result;
}

PyObject *task_generator(PyObject *self, PyObject *args)
{
    int task_time;
    Py_ssize_t n_tasks;

    if (!PyArg_ParseTuple(args, "ni", &n_tasks, &task_time))
        return NULL;

    PyObject *result;

    auto tasks = make_tasks<int>(n_tasks, task_time);

    auto start_time = std::chrono::system_clock::now();
    auto unpacked_tasks = unpack_tasks<int>(tasks, task_time);
    auto end_time = std::chrono::system_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    PyObject *process_duration = PyLong_FromLongLong(duration_ms);

    PyObject *py_tasks = PyList_New(n_tasks);
    for (auto id = 0; id < n_tasks; ++id)
    {
        PyObject *number = PyLong_FromLong(unpacked_tasks.at(id));
        PyList_SetItem(py_tasks, id, number);
    }

    result = Py_BuildValue("OO", py_tasks, process_duration);

    Py_XDECREF(py_tasks);
    Py_XDECREF(process_duration);

    return result;
}