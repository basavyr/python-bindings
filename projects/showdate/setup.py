from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('showdate', include_dirs=['usr/bin/include'], libraries=[
                     'pthread', 'stdc++'], sources=['date.cc'], extra_compile_args=['-std=c++14'], language=['c++'])

setup(name='showdate', version='1.0', description='Returns a string from input and the corrent time and date',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
