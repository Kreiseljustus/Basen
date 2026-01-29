@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe --file=Build.lua vs2022
popd

call Build-Assimp.bat
call Build-Libs-Windows.bat
pause