#!/bin/sh
set -e

ORIG_DIR=$(pwd)
echo "origin directory $ORIG_DIR"

# Update headers 
cd /usr/src/include/
echo "<====updating headers"
make install

# Compiling kernel syscalls 
cd /usr/src/lib
echo "<====compiling kernel syscalls"
make
make install

# Compiling libraries
cd /usr/src/lib/posix/
echo "<====compiling libraries"
make Makefile

cd /usr/src/
make libraries

# Compiling servers
cd /usr/src/servers/
echo "<====compiling servers"
make image
make install

# Compile the kernel
cd /usr/src/tools/
echo "<====compiling the kernel"
make hdboot
echo "<====installing the kernel"
make install

cd $ORIG_DIR
