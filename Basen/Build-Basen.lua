project "Basen"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",
      "../Vendor/bgfx/include",
      "../Vendor/bx/include",
      "../Vendor/bimg/include",
      "../Vendor/glfw/include",
      "../Vendor/Assimp/include",
      "../Vendor/spdlog/include"
   }

   libdirs {
    "../Vendor/bgfx/.build/win64_vs2022/bin",
    "../Vendor/bx/.build/win64_vs2022/bin",
    "../Vendor/bimg/.build/win64_vs2022/bin",
    "../Vendor/glfw/lib-vc2022",
    "../Vendor/Assimp/bin",
    "../Vendor/Assimp/lib/x64/",
    "../Vendor/spdlog/build/Debug",
    "../Vendor/spdlog/build/Release"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
        links { "bgfxDebug", "bimgDebug", "bxDebug", "glfw3", "assimp-vc143-mt" }
       defines { "DEBUG", "BX_CONFIG_DEBUG", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       links { "bgfxRelease", "bimgRelease", "bxRelease", "glfw3", "assimp-vc143-mt"}
       defines { "RELEASE", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       links { "bgfxRelease", "bimgRelease", "bxRelease", "glfw3", "assimp-vc143-mt" }
       defines { "DIST", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Release"
       optimize "On"
       symbols "Off"
