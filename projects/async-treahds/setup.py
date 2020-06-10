from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('asyncxx', include_dirs=['usr/bin/include'], libraries=[
                     'pthread', 'stdc++'], sources=['async-treahds.cc'], extra_compile_args=['-std=c++14'], language=['c++'])

setup(name='asyncxx', version='1.0', description='Works with async threads in CXX',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
