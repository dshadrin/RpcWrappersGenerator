@echo off
set PATH=d:\msys64\mingw64\bin;%PATH%
set BOOST_LIBRARYDIR=d:\usr\lib64
rmdir /S /Q build
rmdir /S /Q bin
mkdir build
cd build
cmake .. -G"MinGW Makefiles" -DPRJ_INSTALL_DIR:STRING="install"
pause
