# Generating python modules with `C/C++`

## General focus - Darwin Architecture

In this document a walkthrough on how to export modules with actual working methods into Python, from `C/C++`.

## Issues with CentOS 

1. After setting up the container with the following script:

```yml
  # CENTOS
  job-2-centos:
    docker:
      - image: "centos:latest"
    steps:
      - checkout
      - run:
          name: install updates
          command: yum -y update && yum -y upgrade
      - run:
          name: install which package so we can check what is good
          command: yum -y install which
      - run:
          name: install dev package
          command: dnf groupinstall -y "Development Tools"
      - run:
          name: install python2 and python3 with dnf
          command: dnf install -y python2 python3 # ----> the base packages
```

There were some issues with trying to **build** the Python extension written in `C++`. This is due to a first error: *missing `"Python.h"`* header file. In order to get that sorted, the python **development** packages must be installed (the base ones which were previously installed are not enough).
The devel packages can be found here (for python2): https://centos.pkgs.org/8/okey-x86_64/python2-devel-2.7.15-24.el8.x86_64.rpm.html

The devel packages for python3 can be downloaded from here (for Centos8): [link](https://centos.pkgs.org/8/centos-appstream-x86_64/python36-devel-3.6.8-2.module_el8.1.0+245+c39af44f.x86_64.rpm.html)

```bash
dnf install python36-devel
```

2. Issue with missing file or dir:

```bash
"gcc: error: /usr/lib/rpm/redhat/redhat-hardened-cc1: No such file or directory"
```

**Solution** found [here](https://gist.github.com/yograterol/99c8e123afecc828cb8c#file-gistfile1-txt):

```bash
sudo dnf install redhat-rpm-config
```

2. Issue with building the python script:

```bash
Compile error: “g++: error trying to exec 'cc1plus': execvp: No such file or directory”
```

**Solution** found [here](https://stackoverflow.com/questions/8878676/compile-error-g-error-trying-to-exec-cc1plus-execvp-no-such-file-or-dir/22072238) with the command given in the [following answer on that post](https://stackoverflow.com/a/21154624/8295213).

On the same issue: [this SO post](https://stackoverflow.com/questions/11912878/gcc-error-gcc-error-trying-to-exec-cc1-execvp-no-such-file-or-directory).

3. Issue with running the python test file after successful building with python2

When attempting to run the python test file from the location where the shared library was installed, the following error occurred: 
```bash
undefined symbol: _ZNSt8ios_base4InitD1Ev
```

> ***c++filt says that `_ZNSt8ios_base4InitD1Ev` is the decorated/mangled name for `std::ios_base::Init::~Init()`. The `@@GLIBCXX_3.4` is clearly some library versioning tag,***

Taken from [this](https://stackoverflow.com/questions/23286062/undefined-reference-to-symbol-znst8ios-base4initd1evglibcxx-3-4-building-op) post. A comment.

**Temporary fix?**: change the naming of the Init function and the method+module in the same manner as the `simplefunction` extension from **ELK_VM** (in the *pythonBindingsCPP* repo - work in progress).

Some other potential fixes: 
* [this so post](https://stackoverflow.com/questions/23286062/undefined-reference-to-symbol-znst8ios-base4initd1evglibcxx-3-4-building-op)1
* [this so post](https://stackoverflow.com/questions/41833767/gcc-invalid-version-max-error-adding-symbols-bad-value)2


## The `init` function on cross-platform module building - Python2

There is a core difference between the Python Init function (at least when building with python2) between Darwin and Linux architectures.

Namely, 

In order to create the module, python2 interpreter on Darwin (OXS)) loads the init function with the following procedure:

```C++
// module initializer for python2
PyMODINIT_FUNC initshowdate() //! ----> on Darwin the init function must be init<modulename>
{
    Py_InitModule3(moduleName, showdateMethodDef, moduleDoc_py2);
    //the init function for building wth python2
}
```

Another approach found on [this guide](https://stackoverflow.com/a/26464041/8295213), is to name the init function has `init_<modulename>`. (More details [here](https://stackoverflow.com/questions/24226001/importerror-dynamic-module-does-not-define-init-function-initfizzbuzz)).

However, when attempt to build the same module on Linux platform (e.g. Centos), the build process will finish successfully, but when trying to execute a test script that uses the module, it fails due to *missing init function*:

```bash
[root@53fd76cc44ae lib.linux-x86_64-2.7]# python2 test.py 
Traceback (most recent call last):
  File "test.py", line 1, in <module>
    import showdate as x
ImportError: dynamic module does not define init function (initshowdate)
```

In order to fix that, a change in the naming of `init` function should be performed. More precisely:

```c++
// module initializer for python2
PyMODINIT_FUNC initshowdate(void)
{
    Py_InitModule3(moduleName, showdateMethodDef, moduleDoc_py2);
    //the init function for building wth python2
}
#endif
```

### Conclusion

> Python2's Init function must always be named `init<modulename>`

## The `init` function on cross-platform module building - Python3

The init function for Python3's interpreter is loaded correctly if it is declared (on all platforms) in the following manner:

```c++
PyMODINIT_FUNC PyInit_showdate() //the init function when building with python3
{
    return PyModule_Create(&showdateModuleDef);
}
```

