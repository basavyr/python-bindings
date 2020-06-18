from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('mclass', include_dirs=['usr/bin/include'], libraries=[
                     'pthread', 'stdc++'], sources=['class-module.cc'], extra_compile_args=['-std=c++14'], language=['c++'])

setup(name='mclass', version='1.0', description='Works with Python custom types - Class objects',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
