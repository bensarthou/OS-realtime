#!/bin/bash
if [ x$BUILD_EXT = x ]
then
        export BUILD_EXT=.exe
        export BUILD_DIR=build$BUILD_EXT
fi

${CROSS_COMPILE}g++ -std=c++11 -Wall -Wextra -I${BUILD_DIR}/include td$1/td$1$2_main.cpp -o ${BUILD_DIR}/td$1$2${BUILD_EXT} -lpthread -lpmrtos -lrt -L${BUILD_DIR}/lib
