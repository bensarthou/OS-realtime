#!/bin/bash
if [ x$BUILD_EXT = x ]
then
        export BUILD_EXT=.exe
        export BUILD_DIR=build$BUILD_EXT
fi

mkdir -p ${BUILD_DIR}
mkdir -p ${BUILD_DIR}/include
mkdir -p ${BUILD_DIR}/lib
mkdir -p ${BUILD_DIR}/obj
SrcFiles=`ls td$1/*.cpp | grep -v main`
${CROSS_COMPILE}g++ -std=c++11 -Wall -c -g -fpic -I${BUILD_DIR}/include ${SrcFiles}
mv *.o ${BUILD_DIR}/obj/
${CROSS_COMPILE}g++ -shared -o libpmrtos.so ${BUILD_DIR}/obj/*.o
mv libpmrtos.so ${BUILD_DIR}/lib/
cp -p td$1/*.h* ${BUILD_DIR}/include
