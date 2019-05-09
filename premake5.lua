workspace "Just"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }    
    
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    -- Include directories relative to root folder (solution directory)
    IncludeDir = {}
    IncludeDir["glfw"] = "Just/vendor/glfw/include"

    include "Just/vendor/glfw"

    project "Just"
        location "Just"
        kind "StaticLib"
        language "C++"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        defines
        {
            "_CRT_SECURE_NO_WARNINGS"
        }

        includedirs
        {
            "%{prj.name}/src",
            "%{prj.name}/vendor/spdlog/include",
            "%{IncludeDir.glfw}"
        }

        links
        {
            "glfw",
            "opengl32.lib"
        }

        filter "system:windows"
            cppdialect "Default"
            staticruntime "on"
            systemversion "latest"

            defines
            {
                "JST_PLATFORM_WINDOWS",
                "JST_BUILD_DLL"
            }

        filter "configurations:Debug"
            defines "JST_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "JST_RELEASE"
            optimize "On"

        filter "configurations:Distribution"
            defines "JST_DISTRIBUTION"
            optimize "On"

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "Default"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "Just/vendor/spdlog/include",
            "Just/src"
        }

        links
        {
            "Just"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "JST_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "JST_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "JST_RELEASE"
            optimize "On"

        filter "configurations:Distribution"
            defines "JST_DISTRIBUTION"
            optimize "On"