#!/bin/sh
uname > os
os_val="$(cat os)"
darwin="Darwin"
if [ "$os_val"="$darwin" ]; then
	echo "We on that OSX!!!"
else
	echo "We on that UNIX..."
fi
