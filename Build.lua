-- premake5.lua
workspace "Basen"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Basen-Editor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus", "/permissive-", "/utf-8" }

OutputDir = "build/%{cfg.buildcfg}-%{prj.name}"

group "Basen"
	include "Basen/Build-Basen.lua"
group ""

include "Basen Editor/Build-Basen-Editor.lua"