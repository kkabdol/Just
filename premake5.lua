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
    IncludeDir["glad"] = "Just/vendor/glad/include"

    include "Just/vendor/glfw"
    include "Just/vendor/glad"

    project "Just"
        location "Just"
        kind "SharedLib"
        language "C++"

        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "jstpch.h"
        pchsource "Just/src/jstpch.cpp"

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
            "%{IncludeDir.glfw}",
            "%{IncludeDir.glad}"
        }

        links
        {
            "glfw",
            "glad",
            "opengl32.lib"
        }

        filter "system:windows"
            cppdialect "Default"
            staticruntime "off"
            systemversion "latest"

            defines
            {
                "JST_PLATFORM_WINDOWS",
				"JST_DYNAMIC_LINK",
                "JST_BUILD_DLL",
                "GLFW_INCLUDE_NONE"
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
        staticruntime "off"

        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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

		prebuildcommands
		{
			("{COPY} ../bin/" .. outputdir .. "/Just/Just.dll %{cfg.buildtarget.directory}" ) 
		}

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "JST_PLATFORM_WINDOWS",
				"JST_DYNAMIC_LINK"
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