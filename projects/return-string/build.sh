echo '*********************************'
echo 'CLEANING UP THE MESS'
echo '*********************************'
rm *.out
rm -rf build/*
echo '*********************************'
echo 'Building the C++ extenstion for Python@2'
echo '*********************************'
/usr/bin/python2 setup.py build
echo '*********************************'
echo 'Testing the C++ extenstion for Python@2'
echo '*********************************'
# cp test.py build/lib.macosx-10.15-x86_64-2.7/test.py
cd build/lib*
cp ../../test.py .
/usr/bin/python2 test.py
# /usr/bin/python2 build/lib.macosx-10.15-x86_64-2.7/test.py
echo '*********************************'
echo 'Building the C++ extenstion for Python@3'
echo '*********************************'
# don't clear the build directory after the first build part
cd ..
cd .. # go back in the main sub-project after buid on v2
/usr/bin/python3 setup.py build
echo '*********************************'
echo 'Testing the C++ extenstion for Python@3'
echo '*********************************'
cd build/lib.macosx-10.14*
cp ../../test.py .
/usr/bin/python3 test.py
# cp test.py build/lib.macosx-10.14-x86_64-3.7/test.py
# cd build/lib.macosx-10.14-x86_64-3.7/
# /usr/bin/python3 build/lib.macosx-10.14-x86_64-3.7/test.py
echo '*********************************'
echo 'Building and Testing on both versions of Python finished...'
echo '*********************************'
