#pragma once

#include "Just/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Just
{
	template class JUST_API std::shared_ptr< spdlog::logger >;

	class JUST_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr< spdlog::logger >& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr< spdlog::logger >& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr< spdlog::logger > s_CoreLogger;
		static std::shared_ptr< spdlog::logger > s_ClientLogger;
	};
}

// Core log macros
#ifdef JST_BUILD_LIBRARY
#define JST_CORE_TRACE(...)		::Just::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JST_CORE_INFO(...)		::Just::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JST_CORE_WARN(...)		::Just::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JST_CORE_ERROR(...)		::Just::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JST_CORE_CRITICAL(...)	::Just::Log::GetCoreLogger()->critical(__VA_ARGS__)
#else
#define JST_CORE_TRACE(...)
#define JST_CORE_INFO(...)
#define JST_CORE_WARN(...)
#define JST_CORE_ERROR(...)
#define JST_CORE_FATAL(...)
#endif // JST_BUILD_LIBRARY

// Client log macros
#define JST_TRACE(...)		::Just::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JST_INFO(...)		::Just::Log::GetClientLogger()->info(__VA_ARGS__)
#define JST_WARN(...)		::Just::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JST_ERROR(...)		::Just::Log::GetClientLogger()->error(__VA_ARGS__)
#define JST_CRITICAL(...)	::Just::Log::GetClientLogger()->critical(__VA_ARGS__)