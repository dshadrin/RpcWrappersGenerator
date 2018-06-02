#!/bin/sh
rm -rf build
rm -rf bin
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DPRJ_INSTALL_DIR:STRING="install"

