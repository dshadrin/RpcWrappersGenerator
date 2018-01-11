#!/bin/sh
rm -rf build
rm -rf bin
mkdir build
cd build
cmake .. -G"Unix Makefiles" -DPRJ_BUILD_TARGET:STRING="linux" -DPRJ_BUILD_TYPE:STRING="Release" -DPRJ_INSTALL_DIR:STRING="install"
