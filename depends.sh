#!/bin/bash

#this project depends on blade,log4cpp
# the "=" can't have blank bwtween it 
current_dir=$(cd $(dirname $0) && pwd)
cd /tmp
# if must have blank beside "[" and "]"
if [ ! -d "log4cpp-codegit" ]; then
	git clone http://git.code.sf.net/p/log4cpp/codegit log4cpp-codegit
fi
cd log4cpp-codegit
./autogen.sh
./configure
make
make check
sudo make install

echo -n "install log4cpp succeed."
cd $current_dir
