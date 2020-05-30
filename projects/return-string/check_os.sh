#!/bin/sh
uname >os
current_os="$(cat os)" # the platform on which the project is built
darwin="Darwin"        # check if Apple's OSX
if [ "$current_os" == "$darwin" ]; then
	./build_darwin.sh
else
	./build_unix.sh
fi
./wipebuild.sh
