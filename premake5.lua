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
    IncludeDir["imgui"] = "Just/vendor/imgui"
	IncludeDir["glm"] = "Just/vendor/glm"

    group "Dependencies"
        include "Just/vendor/glfw"
        include "Just/vendor/glad"
        include "Just/vendor/imgui"
    group ""
    
    project "Just"
        location "Just"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"
            
        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
        
        pchheader "jstpch.h"
        pchsource "Just/src/jstpch.cpp"

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
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
            "%{IncludeDir.glad}",
            "%{IncludeDir.imgui}",
			"%{IncludeDir.glm}"
        }

        links
        {
            "glfw",
            "glad",
            "imgui",
            "opengl32.lib"
        }

        filter "system:windows"
            systemversion "latest"

            defines
            {
                "JST_PLATFORM_WINDOWS",
				"JST_BUILD_LIBRARY",
                "GLFW_INCLUDE_NONE"
            }

            buildoptions { "/Zc:__cplusplus" }

        filter "configurations:Debug"
            defines "JST_DEBUG"
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines "JST_RELEASE"
            runtime "Release"
            optimize "On"

        filter "configurations:Distribution"
            defines "JST_DISTRIBUTION"
            runtime "Release"
            optimize "On"

    project "Sandbox"
        location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
        
        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "Just/vendor/spdlog/include",
            "Just/src",
            "Just/vendor",
            "%{IncludeDir.glm}"
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

            buildoptions { "/Zc:__cplusplus" }

        filter "configurations:Debug"
            defines "JST_DEBUG"
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines "JST_RELEASE"
            runtime "Release"
            optimize "On"

        filter "configurations:Distribution"
            defines "JST_DISTRIBUTION"
            runtime "Release"
            optimize "On"