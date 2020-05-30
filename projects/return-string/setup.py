from distutils.core import setup, Extension

# needs the 'stdc++' library in order to compile with python3 on Debian and Ubuntu
module_0 = Extension('showstring', include_dirs=[], libraries=[
                     'pthread', 'stdc++'], sources=['string.cc'],)

setup(name='showstring', version='1.0', description='Returns a string from input. Simple C++ Python module',
      url='http://www.elk.nipne.ro', ext_modules=[module_0])
