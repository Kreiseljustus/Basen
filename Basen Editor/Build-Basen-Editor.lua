project "Basen-Editor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files {
    "Source/**.h",
    "Source/**.cpp",
    "../Vendor/bgfx-imgui/bgfx-imgui/src/imgui_impl_bgfx.cpp",
    "../Vendor/dear-imgui/imgui.cpp",
    "../Vendor/dear-imgui/imgui_draw.cpp",
    "../Vendor/dear-imgui/imgui_tables.cpp",
    "../Vendor/dear-imgui/imgui_widgets.cpp",
    "../Vendor/dear-imgui/backends/imgui_impl_glfw.cpp"
}

   includedirs
   {
      "Source",

	  -- Include Core
	  "../Basen/Source",

      -- Vendors
      "../Vendor/dear-imgui/",
      "../Vendor/dear-imgui/backends/",
      "../Vendor/bgfx/include",
      "../Vendor/bx/include",
      "../Vendor/bimg/include",
      "../Vendor/glfw/include",
      "../Vendor/Assimp/include",
      "../Vendor/spdlog/include",
      "../Vendor/bgfx-imgui/",
      "../Vendor/entt/single_include"
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
       defines { "DEBUG", "BX_CONFIG_DEBUG", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }
       runtime "Release"
       optimize "On"
       symbols "Off"

    filter "system:linux"
    defines { "LINUX" }
    libdirs {
        "../Vendor/bgfx/.build/linux64_gcc/bin",
        "../Vendor/glfw/lib"
    }

    filter "configurations:Debug"
        links { "bxDebug", "bimgDebug", "bgfxDebug", "glfw", "GL", "X11", "pthread", "dl" }

    filter "configurations:Release"
        links { "bxRelease", "bimgRelease", "bgfxRelease", "glfw", "GL", "X11", "pthread", "dl" }

    filter "configurations:Dist"
        links { "bxRelease", "bimgRelease", "bgfxRelease", "glfw", "GL", "X11", "pthread", "dl" }