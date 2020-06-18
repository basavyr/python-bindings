import mclass

mylist = [10, 20, 30]
pynorm = 2
pywhich = 3
pywith = 9
mystring = 'MCLass'
mybstring = mystring.encode(encoding='utf-8')
y = mclass.MClass(mylist, pynorm)
# print(y.py_list)
# print(y.py_norm)
print(y.normalize())
