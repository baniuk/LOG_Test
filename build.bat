rem temporary script for testing cmake
call tools\clean.bat
cmake -G "NMake Makefiles"
rem calls warper script - correct env must be set http://www.mail-archive.com/cmake@cmake.org/msg38597.html
CMake_trash\make_warper_script.bat
