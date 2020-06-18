rm -rf build/*
python3 setup.py build
cp test.py build/lib*
cd build/lib*
python3 test.py
