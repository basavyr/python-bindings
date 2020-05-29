import showstring as x

print("")
print("**** MODULE IMPLEMENTATION TEST ****")
print("")

# runs the C-extension implementation into python3


def run_module(user):
    print(x.showstring(user))


y = "Darwin"
run_module(y)
