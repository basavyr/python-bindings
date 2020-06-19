import mclass
import numpy as np
import random as rd


def GiveRandomArray(size, left, right):
    rand_array = []
    for id in range(size+1):
        rnd = rd.randrange(left, right+1)
        rand_array.append(rnd)
    return rand_array


ARR_SIZE = 121
LEFT = 0
RIGHT = 110
RAND_PARAMS = [ARR_SIZE, LEFT, RIGHT]

pylist = GiveRandomArray(RAND_PARAMS[0], RAND_PARAMS[1], RAND_PARAMS[2])

PYNORM = 2
PYWHICH = 3
PYWITH = 9
PYSTRING = 'MCLass - Class Module'
PYBYTESTRING = PYSTRING.encode(encoding='utf-8')

myVars = [pylist, PYNORM, PYWHICH, PYWITH, PYBYTESTRING]


def UpdateVars(vars, rand_params):
    new_list = GiveRandomArray(rand_params[0], rand_params[1], rand_params[2])
    vars[0] = new_list
    return vars


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


print(init_class(mclass, myVars, 1).sort(-1))


def sort_arrays(list):
    local_vars = [list]
    sorted_list = init_class(mclass,  local_vars, 1).sort()
    return sorted_list


class ArrayOps:
    def __init__(self, array, params):
        self.array = array
        self.params = params

    def check_data(self):
        print(f'Class variables are: {self.array} | {self.params}')


x = ArrayOps([1, 2, 23], [1, 2])
x.check_data()

# t0 = GiveRandomArray(RAND_PARAMS[0], RAND_PARAMS[1], RAND_PARAMS[2])
# print(t0)
# t0=sort_arrays(t0)
# print(t0)


# for n_arg in range(6):
#     w = init_class(mclass, myVars, n_arg)
#     # if(n_arg > 0):
#     # print(w.sort())
#     UpdateVars(myVars, RAND_PARAMS)
