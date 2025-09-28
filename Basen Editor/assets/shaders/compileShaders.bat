@echo off
setlocal

REM Get the directory of this batch file
set SCRIPT_DIR=%~dp0

REM Path to shaderc (next to this .bat)
set SHADERC=%SCRIPT_DIR%shadercDebug.exe

REM Shader source folder (this folder)
set SHADERS=%SCRIPT_DIR%

REM Path to bgfx includes (relative to project root)
set BGFX_INC=%SCRIPT_DIR%..\..\..\Vendor\bgfx\src

REM Varying def file
set VARYING=%SCRIPT_DIR%mesh_varying.def.sc

REM --------------------------
REM Direct3D11 (s_5_0 profile)
"%SHADERC%" -f "%SHADERS%vs_mesh.sc" -o "%SHADERS%vs_mesh_dx11.bin" --type vertex   --platform windows --profile s_5_0 --varyingdef "%VARYING%" -i "%BGFX_INC%"
"%SHADERC%" -f "%SHADERS%fs_mesh.sc" -o "%SHADERS%fs_mesh_dx11.bin" --type fragment --platform windows --profile s_5_0 --varyingdef "%VARYING%" -i "%BGFX_INC%"

REM OpenGL (GLSL 1.20)
"%SHADERC%" -f "%SHADERS%vs_mesh.sc" -o "%SHADERS%vs_mesh_gl.bin" --type vertex   --platform windows --profile 120 --varyingdef "%VARYING%" -i "%BGFX_INC%"
"%SHADERC%" -f "%SHADERS%fs_mesh.sc" -o "%SHADERS%fs_mesh_gl.bin" --type fragment --platform windows --profile 120 --varyingdef "%VARYING%" -i "%BGFX_INC%"

REM Vulkan (SPIR-V)
"%SHADERC%" -f "%SHADERS%vs_mesh.sc" -o "%SHADERS%vs_mesh_vk.bin" --type vertex   --platform linux --profile spirv --varyingdef "%VARYING%" -i "%BGFX_INC%"
"%SHADERC%" -f "%SHADERS%fs_mesh.sc" -o "%SHADERS%fs_mesh_vk.bin" --type fragment --platform linux --profile spirv --varyingdef "%VARYING%" -i "%BGFX_INC%"

REM Metal (macOS/iOS)
"%SHADERC%" -f "%SHADERS%vs_mesh.sc" -o "%SHADERS%vs_mesh_mtl.bin" --type vertex   --platform osx --profile metal --varyingdef "%VARYING%" -i "%BGFX_INC%"
"%SHADERC%" -f "%SHADERS%fs_mesh.sc" -o "%SHADERS%fs_mesh_mtl.bin" --type fragment --platform osx --profile metal --varyingdef "%VARYING%" -i "%BGFX_INC%"

echo Shader compilation complete.
pause
endlocal
