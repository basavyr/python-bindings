#!/bin/sh
uname > os
os_val="$(cat os)"
darwin="Darwinnn"
if [ "$os_val"="$darwin" ]; then
	./build_darwin.sh
else
	./build_unix.sh
fi
