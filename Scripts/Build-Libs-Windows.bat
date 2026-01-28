@echo off
setlocal enabledelayedexpansion

REM Find Visual Studio
for /f "usebackq tokens=*" %%i in (`
 "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" ^
 -latest -products * -requires Microsoft.Component.MSBuild ^
 -find MSBuild\**\Bin\MSBuild.exe
`) do (
    set MSBUILD=%%i
)

if not defined MSBUILD (
    echo ERROR: MSBuild not found
    exit /b 1
)

REM Go to bgfx directory
cd /d %~dp0..\Vendor\bgfx

echo Using MSBuild: %MSBUILD%

REM Generate solution
call ..\bx\tools\bin\windows\genie.exe vs2022 --with-dynamic-runtime

REM Build with /MD and /MDd
"%MSBUILD%" .build\projects\vs2022\bgfx.sln ^
 /p:Configuration=Release ^
 /p:Platform=x64 ^
 /p:RuntimeLibrary=MultiThreadedDLL

"%MSBUILD%" .build\projects\vs2022\bgfx.sln ^
 /p:Configuration=Debug ^
 /p:Platform=x64 ^
 /p:RuntimeLibrary=MultiThreadedDebugDLL

echo bgfx build finished
pause
