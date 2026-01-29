project "Basen"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "on"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",
      "../Vendor/bgfx/include",
      "../Vendor/bx/include",
      "../Vendor/bimg/include",
      "../Vendor/glfw/include",
      "../Vendor/Assimp/include",
      "../Vendor/Assimp/build/include",
      "../Vendor/spdlog/include",
      "../Vendor/dear-imgui/",
      "../Vendor/bgfx-imgui/",
      "../Vendor/entt/single_include"
   }

   libdirs {
    "../Vendor/bgfx/.build/win64_vs2022/bin",
    "../Vendor/bx/.build/win64_vs2022/bin",
    "../Vendor/bimg/.build/win64_vs2022/bin",
    "../Vendor/glfw/lib-vc2022",
    "../Vendor/Assimp/build/bin/Release",
    "../Vendor/Assimp/build/lib/Release",
    "../Vendor/spdlog/build/Debug",
    "../Vendor/spdlog/build/Release"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

    filter "system:linux" 
    defines { "LINUX" } 
    links { "dl", "pthread", "X11" }

   filter "configurations:Debug"
        links { "bgfxDebug", "bimgDebug", "bxDebug", "glfw3_mt", "assimp-vc143-mt" }
       defines { "DEBUG", "BX_CONFIG_DEBUG", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       links { "bgfxRelease", "bimgRelease", "bxRelease", "glfw3_mt", "assimp-vc143-mt"}
       defines { "RELEASE", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       links { "bgfxRelease", "bimgRelease", "bxRelease", "glfw3_mt", "assimp-vc143-mt" }
       defines { "DIST", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Release"
       optimize "On"
       symbols "Off"
