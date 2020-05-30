FILE=os # deletes the os file only if it is present
if [[ -f "$FILE" ]]; then
    rm os
    # echo 'Cleaned tree of OS info'
fi
rm -rf build/*

# this part finds all the .out files and deletes them safely
# answer to this found here https://askubuntu.com/questions/377438/how-can-i-recursively-delete-all-files-of-a-specific-extension-in-the-current-di
# https://askubuntu.com/a/377442/1003173
find . -maxdepth 1 -name  "*.out" -delete