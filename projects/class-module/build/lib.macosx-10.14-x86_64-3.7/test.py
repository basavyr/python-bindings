import mclass
import numpy as np

pyList = [23, 5324, 23, 432, 4, 32, 423, 3432, 4, 23, 4532, 41, 41]
pyNorm = 2
pyWhich = 3
pyWith = 9
myString = 'MCLass'
myByteString = myString.encode(encoding='utf-8')

myVars = [pyList, pyNorm, pyWhich, pyWith, myByteString]


def init_class(cls, vars, N_args):
    if(N_args == 0):
        retval = cls.MClass()
    if(N_args == 1):
        retval = cls.MClass(vars[0])
    if(N_args == 2):
        retval = cls.MClass(vars[0], vars[1])
    if(N_args == 3):
        retval = cls.MClass(vars[0], vars[1], vars[2])
    if(N_args == 4):
        retval = cls.MClass(vars[0], vars[1], vars[2], vars[3])
    if(N_args == 5):
        retval = cls.MClass(vars[0], vars[1], vars[2], vars[3], vars[4])
    return retval


for n_arg in range(6):
    w = init_class(mclass, myVars, n_arg)
    counter = w.name()[5]
    # print(f'There are {counter} objects not initialized in the class constructor')
    if(n_arg > 0):
        print(w.sort())
