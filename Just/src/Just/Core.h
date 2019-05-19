#pragma once

#ifdef JST_PLATFORM_WINDOWS
#ifdef JST_DYNAMIC_LINK
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

#ifdef JST_DEBUG
	#define JST_ENABLE_ASSERTS
#endif

#ifdef JST_ENABLE_ASSERTS
	#define JST_ASSERT(x, ...) { if(!(x)) { JST_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JST_CORE_ASSERT(x, ...) { if(!(x)) { JST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JST_ASSERT(x, ...) 
	#define JST_CORE_ASSERT(x, ...)
#endif // JST_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define JST_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#ifdef JST_PLATFORM_WINDOWS
#define JST_STRINGIZE( L )     #L 
#define JST_MAKESTRING( M, L ) M(L)
#define JST_LINE JST_MAKESTRING( JST_STRINGIZE, __LINE__ )
#define JST_WARNING __FILE__ "(" JST_LINE ") : Warning: "
#endif // JST_PLATFORM_WINDOWS