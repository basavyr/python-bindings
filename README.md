# Python Bindings

A unified project that contains multiple implementations of C/C++ functions exported as modules into Python.

The repository is organized in smaller projects, where each project implements a Python module with `C++` that does a specific task (e.g. return a string, return the current time and so on).  A project can have a module with multiple methods, if they are defined in their respective `C++` source code.

An individual project has some core parts which are consistent across the entire repository's internal structure. Namely, each sub project has:

* a main `C++` file which contains the actual methods that should be embedded into Python. (usually the name is `sub-project-name.cc`).
  * This source file basically contains all the `PyObject` methods that implement a specific functionality.
* a main header file which initializes the created methods into a Module, that must be exported into Python.
  * The header file must have the methods embedded into a module compatible with both `python@2` and also `python@3`.
  * This is done by creating a general `IF` condition, where compiler checks at build time what `python` interpreter has been selected (e.g. `/usr/bin/python2` or `/usr/bin/python3`).
  * More details about **generating python modules with `C/C++`** can be read [here](docs.md).