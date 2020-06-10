from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('twister', include_dirs=['usr/bin/include'], libraries=[
                     'pthread', 'stdc++'], sources=['random-twister.cc'], extra_compile_args=['-std=c++14'], language=['c++'])

setup(name='twister', version='1.0', description='Generates random numbers using the Mersenne Twister CXX',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
