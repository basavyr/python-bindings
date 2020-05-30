import showstring as x

print("")
print("**** MODULE IMPLEMENTATION TEST ****")
print("")

# runs the C-extension implementation into python3


def run_module(user):
    print(x.showstring(user))


user = open('../../os', 'r').read().split('\n')[0]

platform = ' '

if(user == 'Darwin'):
    platform = 'Darwin'
else:
    platform = 'Linux'

y = "Darwin"
run_module(platform)
