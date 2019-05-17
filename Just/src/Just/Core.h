#pragma once

#ifdef JST_PLATFORM_WINDOWS
#if JST_DYNAMIC_LINK
	#ifdef JST_BUILD_DLL
		#define JUST_API __declspec( dllexport )
	#else
		#define JUST_API __declspec( dllimport )
	#endif // JST_BUILD_DLL
#else
	#define JUST_API
#endif // JST_DYNAMIC_LINK
#else
#error Just only supports Windows!
#endif // JST_PLATFORM_WINDOWS

#ifdef JST_ENABLE_ASSERTS
#define JST_ASSERT(x, ...) { if(!(x)) { JST_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define JST_CORE_ASSERT(x, ...) { if(!(x)) { JST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define JST_ASSERT(x, ...) 
#define JST_CORE_ASSERT(x, ...)
#endif // JST_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define JST_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)