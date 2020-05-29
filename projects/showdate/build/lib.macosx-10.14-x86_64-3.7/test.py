import showdate as x

print("")
print("**** MODULE IMPLEMENTATION TEST ****")
print("")

# runs the C-extension implementation into python3


def run_module(user):
    print(x.showdate(user))


y = "Darwin"
run_module(y)
