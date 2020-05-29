from distutils.core import setup, Extension

module_0 = Extension('showdate', include_dirs=['usr/bin/include'], libraries=[
                     'pthread'], sources=['date.cc'],extra_compile_args=['-std=c++14'])

setup(name='showdate', version='1.0', description='Returns a string from input and the corrent time and date',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
