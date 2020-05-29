echo '*********************************'
echo 'Building the C++ extenstion for Python@2'
echo '*********************************'
rm *.out
rm -rf build/*
/usr/bin/python2 setup-date.py build
echo '*********************************'
echo 'Testing the C++ extenstion for Python@2'
echo '*********************************'
cp test.py build/lib.macosx-10.15-x86_64-2.7/test.py
cd build/lib.macosx-10.15-x86_64-2.7/
/usr/bin/python2 test.py
echo '*********************************'
echo 'Building the C++ extenstion for Python@3'
echo '*********************************'
rm *.out
rm -rf build/*
/usr/bin/python3 setup-date.py build
echo '*********************************'
echo 'Testing the C++ extenstion for Python@3'
echo '*********************************'
cp test.py build/lib.macosx-10.14-x86_64-3.7/test.py
cd build/lib.macosx-10.14-x86_64-3.7/
/usr/bin/python3 test.py
echo '*********************************'
echo 'Building and Testing on both versions of Python finished...'
echo '*********************************'
