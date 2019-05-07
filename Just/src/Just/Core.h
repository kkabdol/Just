#pragma once

#ifdef JST_PLATFORM_WINDOWS

#ifdef JST_BUILD_DLL
#define JUST_API __declspec( dllexport )
#else
#define JUST_API __declspec( dllimport )
#endif // JST_BUILD_DLL

#else

#error Just only supports Windows!

#endif // JST_PLATFORM_WINDOWS

#define BIT(x) (1 << x)