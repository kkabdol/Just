workspace "Just"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }
    
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Just"
    location "Just"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "Default"
        staticruntime "off"
        systemversion "latest"

        defines
        {
            "JST_PLATFORM_WINDOWS",
            "JST_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "JST_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "JST_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "JST_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
	kind "ConsoleApp"
    language "C++"

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
        cppdialect "Default"
        staticruntime "off"
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

    filter "configurations:Dist"
        defines "JST_DIST"
        optimize "On"