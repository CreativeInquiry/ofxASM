#! /bin/bash

WD=$(dirname $0)

SRC=asmlib-opencv
DEST=../libs/asmlib-opencv

###

cd $WD

# get latest source
svn -q checkout http://asmlib-opencv.googlecode.com/svn/trunk asmlib-opencv

# remove uneeded makefiles
find $SRC -name "CMakeLists.txt" -delete

# copy sources
mkdir -p $DEST/src
cp -Rv $SRC/src/lib/* $DEST/src

# copy data
mkdir -p ../data
cp -Rv $SRC/data/* ../data

# cleanup
rm -rf $SRC
