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


# ------> reads the os file and checks what platform the system is on
# solution from here https://stackoverflow.com/a/3277511/8295213
os = open('../../os', 'r',).read().split('\n')[0]

is_OSX = 'This is Darwin'
is_Linux = 'This is Linux'

prefix = 'Hey'

platform = ' '

if(os == 'Darwin'):
    # print(is_OSX)
    platform = 'Darwin'
else:
    #     print(is_Linux)
    platform = 'Linux'

run_module(prefix, platform)
