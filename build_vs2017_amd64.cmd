@echo off
rmdir /S /Q build
rmdir /S /Q bin
mkdir build
cd build
copy ..\xerces-c-3.1.1\src\xercesc\util\Xerces_autoconf_config.msvc.hpp ..\xerces-c-3.1.1\src\xercesc\util\Xerces_autoconf_config.hpp
cmake .. -G "Visual Studio 15 2017 Win64" -DPRJ_INSTALL_DIR:STRING="install"
pause
