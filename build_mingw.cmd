@echo off
set PATH=%PATH%;d:\mingw\bin
rmdir /S /Q build
rmdir /S /Q bin
mkdir build
cd build
cmake .. -G"MinGW Makefiles" -DPRJ_BUILD_TARGET:STRING="mingw" -DPRJ_BUILD_TYPE:STRING="Release" -DPRJ_INSTALL_DIR:STRING="install"
pause
