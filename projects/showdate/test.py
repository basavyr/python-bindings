import showdate as x

print("")
print("**** MODULE IMPLEMENTATION TEST ****")
print("")

# runs the C-extension implementation into python3


def run_module(string1, string2):
    print("Method 1")
    print(x.showdate(string2))
    print("Method 2")
    print(x.join(string1, string2))
    print("All methods were tested successfully...")


user = 'Darwin'
prefix = 'Hey'
run_module(prefix, user)
