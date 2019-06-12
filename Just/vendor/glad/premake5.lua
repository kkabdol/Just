project "glad"
    kind "StaticLib"
    language "C"
    cdialect "C11"
    staticruntime "on"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    debugdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"

        filter { "system:windows", "configurations:Debug" }
            runtime "Debug"
            symbols "On"

        filter { "system:windows", "configurations:Release" }
            runtime "Release"
            optimize "On"
        
        filter { "system:windows", "configurations:Distribution" }
            runtime "Release"
            optimize "On"