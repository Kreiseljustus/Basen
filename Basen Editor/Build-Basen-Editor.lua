project "Basen Editor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files {
    "Source/**.h",
    "Source/**.cpp",
    "../Vendor/imgui_impl/**.cpp",
    "../Vendor/imgui_impl/**.h",
    "../Vendor/dear-imgui/imgui.cpp",
    "../Vendor/dear-imgui/imgui_draw.cpp",
    "../Vendor/dear-imgui/imgui_widgets.cpp",
    "../Vendor/dear-imgui/imgui_tables.cpp"
}

   includedirs
   {
      "Source",

	  -- Include Core
	  "../Basen/Source",

      -- Vendors
      "../Vendor/imgui_impl",
      "../Vendor/dear-imgui/",
      "../Vendor/bgfx/include",
      "../Vendor/bx/include",
      "../Vendor/bimg/include",
      "../Vendor/glfw/include",
      "../Vendor/Assimp/include"
   }

   links
   {
      "Basen"
   }

    postbuildcommands {
    'copy /Y "..\\Vendor\\Assimp\\bin\\x64\\assimp-vc143-mt.dll" "%{cfg.targetdir}%"',
    'call assets\\shaders\\compileShaders.bat'
    }


   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG", "BX_CONFIG_DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"