from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('convarray', include_dirs=['usr/bin/include'], libraries=[
                     'pthread', 'stdc++'], sources=['convert-array.cc'], extra_compile_args=['-std=c++14'], language=['c++'])

setup(name='convarray', version='1.0', description='Generates a Python array to a C++ vector',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
