#!/bin/sh
set -e
set -x

libtoolize --automake --copy
aclocal 
autoheader
automake --add-missing --copy
autoconf

./configure --prefix=/usr
