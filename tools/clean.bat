echo off
SETLOCAL ENABLEEXTENSIONS
IF ERRORLEVEL 1 goto errorext

FOR /R %%A IN (*) DO IF %%~nA%%~xA==cmake_install.cmake del /q %%~fA
FOR /R %%A IN (*) DO IF %%~nA%%~xA==CMakeCache.txt del /q %%~fA
FOR /D /R %%X IN (CMakeFiles*) DO rmdir "%%X" /s /q
IF "%1"=="ALL" goto :CLEAR_ALL
goto :EOF

:CLEAR_ALL
rmdir CMake_trash /s /q
rmdir doc\html /s /q
FOR /R %%A IN (*) DO IF %%~nA%%~xA==Makefile del /q %%~fA
FOR /D /R %%X IN (Third_Party\*) DO rmdir "%%X" /s /q
goto :EOF

:errorext
echo Unable to enable extensions