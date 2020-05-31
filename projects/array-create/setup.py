from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('retarray', include_dirs=['usr/bin/include'], libraries=[
                     'pthread', 'stdc++'], sources=['array-create.cc'], extra_compile_args=['-std=c++14'], language=['c++'])

setup(name='retarray', version='1.0', description='Returns an array',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
