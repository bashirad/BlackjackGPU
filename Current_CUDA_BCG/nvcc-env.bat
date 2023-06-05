rem This script sets up the environment for using the NVIDIA compiler, nvcc, on the command line.
rem Run this command then nvcc is in the command path.
rem By R. Coleman, 1 Sep 2018
rem
rem The problem is nvcc depends on MS cl compiler which is not in the default path.

rem Here's the path for VS 2017 Community Edition
rem set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.15.26726\bin\Hostx64\x64;%PATH%

set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64;%PATH%


rem Here's the path for VS 2017 Professional Edition
rem set PATH=c:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.15.26726\bin\Hostx64\x64;%PATH%