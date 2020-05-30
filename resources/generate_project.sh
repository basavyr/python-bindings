#!/bin/sh
echo "Generating the project..."
ProjectName="$1"
cd ../projects/
mkdir $ProjectName
cd $ProjectName
cp ../../resources/wipebuild.sh .
cp ../../resources/check_os.sh .
cp ../../resources/build_unix.sh .
cp ../../resources/build_darwin.sh .
echo "# $ProjectName\nThis is a new project.  \nContent was auto-generated by the script" >about.md
touch "$ProjectName.cc"
touch "$ProjectName.hh"
touch "setup.py"
touch "test.py"
echo "Project was successfully generated..."