#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Desert {

	class DESERT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define DT_CORE_ERROR(...)     ::Desert::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DT_CORE_WARN(...)      ::Desert::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DT_CORE_INFO(...)      ::Desert::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DT_CORE_TRACE(...)     ::Desert::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define DT_ERROR(...)          ::Desert::Log::GetClientLogger()->error(__VA_ARGS__)
#define DT_WARN(...)           ::Desert::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DT_INFO(...)           ::Desert::Log::GetClientLogger()->info(__VA_ARGS__)
#define DT_TRACE(...)          ::Desert::Log::GetClientLogger()->trace(__VA_ARGS__)