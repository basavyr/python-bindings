from distutils.core import setup, Extension

module_0 = Extension('showstring', include_dirs=['/usr/local/include/'], libraries=[
                     'pthread'], sources=['string.cc'],)

setup(name='showstring', version='1.0', description='Returns a string from input. Simple C++ Python module',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
