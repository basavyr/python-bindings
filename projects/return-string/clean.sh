rm -rf build/*
python3 setup-string.py build
cp test.py build/lib.macosx-10.14-x86_64-3.7/test.py
cd build/lib.macosx-10.14-x86_64-3.7/
python3 test.py