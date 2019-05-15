project "glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
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
        cdialect "C11"
        staticruntime "off"
        systemversion "latest"

        filter { "system:windows", "configurations:Debug" }
            symbols "On"

        filter { "system:windows", "configurations:Release" }
            optimize "On"
        
        filter { "system:windows", "configurations:Distribution" }
            optimize "On"